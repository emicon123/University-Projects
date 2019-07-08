package pl.polsl.lab.model;

import java.sql.*;

/**
 * Singleton class creating and returning connection with database
 *
 * @author wojci
 * @version 1.0
 */
public class DbConnection {

    /**
     * Keeps instance of class
     */
    private static DbConnection instance;
    /**
     * Keeps instance of connection
     */
    private Connection connection;

    /**
     * Private constructor of class
     *
     * @param url URL for DB
     * @param user Username for DB
     * @param password Password for DB
     * @param driver DB's driver
     * @throws SQLException database exception
     * @throws ClassNotFoundException exception
     */
    private DbConnection(String url, String user, String password, String driver) throws SQLException, ClassNotFoundException {
        Class.forName(driver);
        this.connection = DriverManager.getConnection(url, user, password);
    }

    /**
     * Public static method returning instance of this class
     *
     * @param url URL for DB
     * @param user Username for DB
     * @param password Password for DB
     * @param driver DB's driver
     * @return instance of this class
     * @throws SQLException database exception
     * @throws ClassNotFoundException exception
     */
    public static DbConnection getInstance(String url, String user, String password, String driver) throws SQLException, ClassNotFoundException {
        if (instance == null) {
            instance = new DbConnection(url, user, password, driver);
        }
        return instance;
    }

    public Connection GetConnection() {
        return connection;
    }

}
