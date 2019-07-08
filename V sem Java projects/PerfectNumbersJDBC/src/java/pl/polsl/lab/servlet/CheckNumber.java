package pl.polsl.lab.servlet;

import java.io.IOException;
import java.io.PrintWriter;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.SQLException;
import java.sql.Statement;
import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;
import pl.polsl.lab.model.PerfectNumbersModel;

/**
 *
 * @author wojci
 * @version 2.0
 */
public class CheckNumber extends HttpServlet {

    /**
     * field representing number to check if it is perfect number
     */
    private int number;

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
        boolean args = false;

        try {
            // loading the JDBC driver
            Class.forName("org.apache.derby.jdbc.ClientDriver");
        } catch (ClassNotFoundException cnfe) {
            System.err.println(cnfe.getMessage());
            return;
        }
        
        if (model == null) {
            model = new PerfectNumbersModel();
            session.setAttribute("model", model);
        }
        
        try  {
            number = Integer.parseInt(request.getParameter("number"));
        } catch (NumberFormatException e) {
            response.sendError(HttpServletResponse.SC_BAD_REQUEST, "Inserted value must be integer");
            args = true;
        } catch (NullPointerException e) {
            out.println("NullPointerException");
            response.sendError(HttpServletResponse.SC_BAD_REQUEST, "NullPointerException");
            args = true;
        } 
        
        try (Connection con = DriverManager.getConnection("jdbc:derby://localhost:1527/lab", "lab", "lab")){
            Statement statement = con.createStatement();;
        } catch (SQLException sqle) {
            System.err.println(sqle.getMessage());
        }
        if (!args) {
            model.setNumber(number);
             
            if (model.isPerfect(number)) {
                out.println("<h3>" + "Value " + model.getNumber() + " is perfect number" + "</h3");
                //statement.executeUpdate("INSERT INTO Dane VALUES (1, 'Nowak', 'Jan', 5.0)");
            } else {
                out.println("<h3>" + "Value " + model.getNumber() + " isn't perfect number" + "</h3>");
            }
        }

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
