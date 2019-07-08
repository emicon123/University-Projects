package pl.polsl.lab.servlet;

import java.io.IOException;
import java.io.PrintWriter;
import java.util.Hashtable;
import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;
import pl.polsl.lab.model.PerfectNumbersException;
import pl.polsl.lab.model.PerfectNumbersModel;

/**
 *
 * @author wojci
 * @version 2.0
 */
public class checkingPNInTheRange extends HttpServlet {

    /**
     * Hashtable representing history of perfect numbers in range
     */
    private Hashtable<String, String> stats;

    /**
     * begin of range
     */
    private int begin;

    /**
     * end of range
     */
    private int end;

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
        stats = new Hashtable<String, String>();
        PerfectNumbersModel model = (PerfectNumbersModel) session.getAttribute("model");
        boolean args = false;

        if (model == null) {
            model = new PerfectNumbersModel();
            session.setAttribute("model", model);
        }
        try {
            begin = Integer.parseInt(request.getParameter("begin"));
            end = Integer.parseInt(request.getParameter("end"));
        } catch (NumberFormatException e) {
            response.sendError(HttpServletResponse.SC_BAD_REQUEST, "Inserted value must be integer");

            args = true;
        } catch (NullPointerException e) {
            out.println("NullPointerException");
            response.sendError(HttpServletResponse.SC_BAD_REQUEST, "NullPointerException");
            args = true;
        }

        if (!args) {
            model.setMinRange(begin);
            model.setMaxRange(end);
            try {
                model.checkingPNInTheRange();
            } catch (PerfectNumbersException e) {
                out.println("Range is invalid");
                response.sendError(HttpServletResponse.SC_BAD_REQUEST, "Range is invalid");

                args = true;
            }

            if (!args) {
                out.println("<h3>Perfect numbers in range: " + model.getMinRange() + ", " + model.getMaxRange() + ": </h3>");
                out.println("<h3>" + model.getArrayOfPN() + "</h3>");
                model.putStats(model.getMinRange() + ", " + model.getMaxRange(), String.valueOf(model.getArrayOfPN()));
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
