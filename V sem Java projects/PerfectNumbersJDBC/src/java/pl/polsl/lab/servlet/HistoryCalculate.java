package pl.polsl.lab.servlet;

import java.io.IOException;
import java.io.PrintWriter;
import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;
import java.util.ArrayList;
import java.util.Hashtable;
import java.util.List;
import java.util.Map;
import javax.servlet.ServletContext;
import javax.servlet.ServletException;
import javax.servlet.http.Cookie;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;
import pl.polsl.lab.model.DbConnection;
import pl.polsl.lab.model.PerfectNumbersModel;

/**
 * @author wojci
 * @version 2.0
 */
public class HistoryCalculate extends HttpServlet {

    /**
     * Processes requests for both HTTP <code>GET</code> and <code>POST</code>
     * methods.
     *
     * @param request servlet request
     * @param response servlet response
     * @throws ServletException if a servlet-specific error occurs
     * @throws IOException if an I/O error occurs
     */
    protected void processRequest(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        response.setContentType("text/html;charset=UTF-8");
        PrintWriter out = response.getWriter();
        HttpSession session = request.getSession(true);
        PerfectNumbersModel model = (PerfectNumbersModel) session.getAttribute("model");

        try {
            Connection connection = GetConnection(this.getServletContext());
            //use cookies to draw last result of nth perfect number calculaltion
            Cookie[] cookies = request.getCookies();
            for (Cookie cookie : cookies) {
                if (cookie.getName().equals("lastResult")) {
                    out.println("Last result in nth perfect number: <br/>");
                    out.println(cookie.getValue() + "<br/>");
                    break;
                }
            }
            out.println("<h3>History of perfect numbers in range:</h3>");
            //read history of perfect number in range from hashtable
            Hashtable<String, String> stats = model.getStats();
            for (Map.Entry<String, String> entry : stats.entrySet()) {
                Statement statement = connection.createStatement();
                ResultSet rs = statement.executeQuery("SELECT * FROM HISTORY");
                while (rs.next()) {
                    while (rs.next()) {
                        out.println("<p>" + rs.getInt("MIN_RANGE"));
                        out.println(" - " + rs.getInt("MAX_RANGE") + " -> ");
                        out.println(rs.getString("PERFECT_NUMBERS") + ";</p>");
                    }
                }
            }
        } catch (Exception e) {
            out.println("Some Exception");
        }

    }

    /**
     * Method that adds new element to conversion history
     *
     * @param element element to add
     * @param connection connection do databse
     * @throws SQLException database exception
     */
    public void AddElement(PerfectNumbersModel element, Connection connection) throws SQLException {
        AddElement(element.getMinRange(), element.getMaxRange(), String.valueOf(element.getArrayOfPN()), connection);
    }

    /**
     * Public method that adds history element to database
     *
     * @param minRange minimum range value
     * @param maxRange maximum range value
     * @param result perfect numbers in range
     * @param connection Connetion with database
     * @throws SQLException database exception
     */
    public void AddElement(int minRange, int maxRange, String result, Connection connection) throws SQLException {

        String statement = "INSERT INTO HISTORY(MIN_RANGE,MAX_RANGE,PERFECT_NUMBERS) VALUES(?,?,?)";
        PreparedStatement preparedStatement = connection.prepareStatement(statement);
        preparedStatement.setInt(1, minRange);
        preparedStatement.setInt(2, maxRange);
        preparedStatement.setString(3, result);
        preparedStatement.executeUpdate();
    }

    /**
     * Private method that gets database connection using servlet parameters
     *
     * @param servletContext Context of servlet
     * @return connection with DB
     * @throws SQLException database exception
     * @throws ClassNotFoundException exception
     */
    private Connection GetConnection(ServletContext servletContext) throws SQLException, ClassNotFoundException {
        return DbConnection.getInstance(servletContext.getInitParameter("url"), servletContext.getInitParameter("user"), servletContext.getInitParameter("password"), servletContext.getInitParameter("driver")).GetConnection();
    }

    /**
     * Handles the HTTP <code>GET</code> method.
     *
     * @param request servlet request
     * @param response servlet response
     * @throws ServletException if a servlet-specific error occurs
     * @throws IOException if an I/O error occurs
     */
    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        processRequest(request, response);
    }

    /**
     * Handles the HTTP <code>POST</code> method.
     *
     * @param request servlet request
     * @param response servlet response
     * @throws ServletException if a servlet-specific error occurs
     * @throws IOException if an I/O error occurs
     */
    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        processRequest(request, response);
    }
}
