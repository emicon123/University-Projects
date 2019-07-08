package pl.polsl.lab.servlet;

import java.io.IOException;
import java.io.PrintWriter;
import java.util.Hashtable;
import java.util.Map;
import javax.servlet.ServletException;
import javax.servlet.http.Cookie;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;
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

        if (model == null) {
            out.println("<h3>The calculation history is empty<h3/>");
        } else {
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
                String range = entry.getKey();
                String result = entry.getValue();
                out.println("<br/>Perfect numbers in range: " + range);
                out.println("<br/>" + result + "<br/>");
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
