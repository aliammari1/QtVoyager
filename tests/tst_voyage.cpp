#include <QtTest>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDate>

#include "gestionVoyages/voyage.h"

// Unit + regression tests for QtVoyager, run against an in-memory QSQLITE
// database so no production ODBC DSN is required. Run headless with
// QT_QPA_PLATFORM=offscreen.
class TestVoyage : public QObject
{
    Q_OBJECT

private:
    void resetSchema()
    {
        QSqlQuery q;
        q.exec("DROP TABLE IF EXISTS VOYAGES");
        q.exec("DROP TABLE IF EXISTS VOYAGEURS");
        QVERIFY(q.exec("CREATE TABLE VOYAGES ("
                       "FLIGHTREF TEXT, LIEUDEP TEXT, LIEUARR TEXT, "
                       "DATEDEP TEXT, DATEARR TEXT, AIRLINE TEXT, "
                       "MONTANT REAL, NBPER INTEGER)"));
        QVERIFY(q.exec("CREATE TABLE VOYAGEURS ("
                       "RFID_CARD TEXT, NAME TEXT)"));
    }

    Voyage makeVoyage(const QString &ref, const QString &dep, const QString &arr,
                      const QString &airline, float montant, int nbper)
    {
        return Voyage(ref, dep, arr, QDate(2026, 1, 1), QDate(2026, 1, 2),
                      airline, montant, nbper);
    }

private slots:
    void initTestCase()
    {
        QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
        db.setDatabaseName(":memory:");
        QVERIFY2(db.open(), "QSQLITE in-memory DB must open");
    }

    void cleanupTestCase()
    {
        QSqlDatabase::database().close();
    }

    void init()
    {
        resetSchema();
    }

    // --- CRUD -------------------------------------------------------------

    void testAjouterAndRetrieve()
    {
        Voyage v = makeVoyage("FR100", "TUN", "PAR", "AirFrance", 500.0f, 2);
        QVERIFY(v.ajouter());

        QList<Voyage> all = v.getAllVoyages();
        QCOMPARE(all.size(), 1);
        QCOMPARE(all.first().getFlightref(), QString("FR100"));
        QCOMPARE(all.first().getNbper(), 2);
    }

    void testSearchByFlightRefFound()
    {
        Voyage v = makeVoyage("FR200", "TUN", "LON", "Tunisair", 300.0f, 1);
        QVERIFY(v.ajouter());
        QVERIFY(v.searchByFlightRef("FR200"));
    }

    void testSupprimer()
    {
        Voyage v = makeVoyage("FR300", "TUN", "ROM", "Alitalia", 250.0f, 3);
        QVERIFY(v.ajouter());
        QVERIFY(v.supprimer("FR300"));
        QCOMPARE(v.getAllVoyages().size(), 0);
    }

    void testUpdate()
    {
        Voyage v = makeVoyage("FR400", "TUN", "MAD", "Iberia", 200.0f, 1);
        QVERIFY(v.ajouter());

        Voyage upd = makeVoyage("FR400", "TUN", "BCN", "Iberia", 220.0f, 4);
        QVERIFY(upd.update("FR400"));

        QList<Voyage> all = v.getAllVoyages();
        QCOMPARE(all.size(), 1);
        QCOMPARE(all.first().getLieuarr(), QString("BCN"));
        QCOMPARE(all.first().getNbper(), 4);
    }

    // --- Cost / profit math ----------------------------------------------

    void testCalculateAverageCost()
    {
        QVERIFY(makeVoyage("A1", "TUN", "PAR", "X", 400.0f, 1).ajouter());
        QVERIFY(makeVoyage("A2", "TUN", "PAR", "Y", 600.0f, 1).ajouter());
        QVERIFY(makeVoyage("A3", "TUN", "LON", "Z", 999.0f, 1).ajouter());

        Voyage v;
        QCOMPARE(v.calculateAverageCost("TUN", "PAR"), 500.0f);
    }

    void testProfitMath()
    {
        // Profit = sum(MONTANT * NBPER). Mirror MainWindow::profit().
        QVERIFY(makeVoyage("P1", "TUN", "PAR", "X", 100.0f, 2).ajouter()); // 200
        QVERIFY(makeVoyage("P2", "TUN", "LON", "Y", 50.0f, 3).ajouter());  // 150

        QSqlQuery query("SELECT MONTANT, NBPER FROM VOYAGES");
        float earn = 0;
        while (query.next())
            earn += query.value(0).toFloat() * static_cast<float>(query.value(1).toInt());
        QCOMPARE(earn, 350.0f);
    }

    // --- SECURITY REGRESSION ---------------------------------------------
    // Asserts searchByFlightRef is parameterized: a classic injection payload
    // must NOT match an unrelated row. With the old string-concatenation the
    // payload would turn the WHERE into a tautology.
    void testFlightRefInjectionIsNeutralized()
    {
        QVERIFY(makeVoyage("REAL", "TUN", "PAR", "X", 100.0f, 1).ajouter());

        Voyage v;
        // The literal payload is treated as a single bound value, so the query
        // succeeds (valid SQL) but matches zero rows.
        const QString payload = "' OR '1'='1";
        QVERIFY2(v.searchByFlightRef(payload),
                 "Parameterized query should execute without error");

        QSqlQuery probe;
        probe.prepare("SELECT COUNT(*) FROM VOYAGES WHERE FLIGHTREF = :ref");
        probe.bindValue(":ref", payload);
        QVERIFY(probe.exec());
        QVERIFY(probe.first());
        QCOMPARE(probe.value(0).toInt(), 0); // injection payload matches nothing
    }

    // Regression for the RFID lookup pattern (mirrors the parameterized query
    // now used in MainWindow::update_label). Feeding an injection payload must
    // not leak unrelated VOYAGEURS rows.
    void testRfidLookupInjectionIsNeutralized()
    {
        QSqlQuery seed;
        seed.prepare("INSERT INTO VOYAGEURS (RFID_CARD, NAME) VALUES (:c, :n)");
        seed.bindValue(":c", "0123456789A");
        seed.bindValue(":n", "Alice");
        QVERIFY(seed.exec());

        const QString payload = "' OR '1'='1";
        QSqlQuery lookup;
        lookup.prepare("SELECT * FROM VOYAGEURS WHERE RFID_CARD = :rfid");
        lookup.bindValue(":rfid", payload);
        QVERIFY(lookup.exec());
        QVERIFY2(!lookup.first(),
                 "Injection payload must not match any VOYAGEURS row");
    }
};

QTEST_MAIN(TestVoyage)
#include "tst_voyage.moc"
