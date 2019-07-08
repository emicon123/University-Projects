package pl.polsl.lab.servlet;

import java.io.IOException;
import java.io.PrintWriter;
import javax.servlet.ServletException;
import javax.servlet.http.Cookie;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;
import pl.polsl.lab.model.PerfectNumbersModel;
import pl.polsl.lab.model.PerfectNumbersException;

/**
 *
 * @author wojci
 * @version 2.0
 */
public class NthPerfectNum extends HttpServlet {

    /**
     * field representing value of nth perfect number
     */
    private int nthValue;

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

        if (model == null) {
            model = new PerfectNumbersModel();
            session.setAttribute("model", model);
        }

        try {
            nthValue = Integer.parseInt(request.getParameter("nthNumber"));
        } catch (NumberFormatException e) {
            response.sendError(HttpServletResponse.SC_BAD_REQUEST, "Inserted value must be integer");

            args = true;
        } catch (NullPointerException e) {
            out.println("NullPointerException");
            response.sendError(HttpServletResponse.SC_BAD_REQUEST, "NullPointerException");
            args = true;
        }

        if (!args) {
            model.setNthPN(nthValue);
            try {
                model.nthPerfectNumber();
            } catch (PerfectNumbersException e) {
                out.println("Value must be positive");
                response.sendError(HttpServletResponse.SC_BAD_REQUEST, "Value must be positive");
                args = true;
            }
            if (!args) {
                out.println("<h3>" + model.getNthPN() + "-th perfect number is " + model.getNthPNResult() + "</h3>");
                String stat = model.getNthPN() + "-th perfect number is " + model.getNthPNResult();
                Cookie cookie = new Cookie("lastResult", stat);
                response.addCookie(cookie);
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
