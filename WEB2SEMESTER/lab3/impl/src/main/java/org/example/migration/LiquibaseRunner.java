package org.example.migration;

import liquibase.Liquibase;
import liquibase.database.Database;
import liquibase.database.DatabaseFactory;
import liquibase.database.jvm.JdbcConnection;
import liquibase.exception.LiquibaseException;
import liquibase.resource.ClassLoaderResourceAccessor;
import lombok.extern.slf4j.Slf4j;
import org.example.dbConnection.JdbcConnector;

import java.io.IOException;
import java.sql.Connection;
import java.sql.SQLException;

@Slf4j
public class LiquibaseRunner {
    public void run() throws SQLException {
        try (Connection connection = JdbcConnector.getConnection()) {
            Database database = DatabaseFactory.getInstance()
                    .findCorrectDatabaseImplementation(new JdbcConnection(connection));

            Liquibase liquibase = new Liquibase(
                    "db/changelog/db.changelog-master.xml",
                    new ClassLoaderResourceAccessor(),
                    database);

            liquibase.update("");
            log.atInfo()
                    .log("✅ Все миграции успешно применены!");

        } catch (LiquibaseException | IOException e) {
            log.atError()
                    .log(e.getMessage());
            throw new RuntimeException(e);
        }
    }
}
