/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package Controller;

import View.ServiceView;
import Model.Model;
import Model.PerfectNumbersException;
import View.*;
import java.io.IOException;
import java.net.ServerSocket;
import java.util.ArrayList;
import java.util.List;
import java.util.logging.Level;
import java.util.logging.Logger;

/**
 *
 * @author wojci
 */
public class ServerController implements Controller {

    final private int PORT = 8888;

    private View theView;
    private Model theModel;
    private ServerSocket serverSocket;

    /**
     * Initial method.
     *
     * @param model , Model instance
     * @throws IOException when port is already bind
     */
    public ServerController(Model model) throws IOException {
        serverSocket = new ServerSocket(PORT);
        this.theModel = model;
        //this.theView = new ServiceView(serverSocket.accept());
    }

    /**
     * Method start controller.
     */
    @Override()
    public void start() {
        /**
         * variable help communicate with client
         */
        String message = "";
        /**
         * variable to select program mode
         */
        String pMode = "";

        try {
            System.out.println("Start server...");
            while (true) {

                try (ServiceView view = new ServiceView(this.serverSocket.accept())) {
                    view.showMessage("HELLO");
                    while (true) {
                        message = view.getMessage();
                        if (message.toUpperCase().equals("QUIT")) {
                            view.showMessage("OK. Quit");
                            break;
                        } else if (message.toUpperCase().equals("MODE")) {
                            view.showMessage("GIVE ME PROGRAM MODE");
                            pMode = view.getMessage();
                            view.showMessage("OK MODE");
                        } else if (message.toUpperCase().equals("PROCEED")) {
                            /**
                             * Proceeding operations
                             */
                            view.showMessage("PROCEEDING");

                            if (pMode.toUpperCase().equals("1")) {
                                /**
                                 * Mode 1
                                 */

                                try {

                                    view.showMessage("GIVE ME MINIMUM RANGE");

                                    int pMinRange = Integer.parseInt(view.getMessage());

                                    view.showMessage("GIVE ME MAXIMUM RANGE");
                                    int pMaxRange = Integer.parseInt(view.getMessage());

                                    /**
                                     * List, to store the PN - used in function
                                     * checkingPNInTheRange
                                     *
                                     * @SuppressWarnings - because numbers are
                                     * correct
                                     */
                                    @SuppressWarnings("unchecked")
                                    List<Integer> listOfPN = new ArrayList<>();

                                    listOfPN = theModel.checkingPNInTheRange(pMinRange, pMaxRange);
                                    view.showMessage("MODE 1 OK");
                                    String listToPrint = view.printList(listOfPN);
                                    view.showMessage(listToPrint);

                                } catch (NumberFormatException e) {
                                    System.err.println("Wrong number/s.");
                                } catch (PerfectNumbersException ex) {
                                    System.err.println(ex.getMessage());
                                }

                            } else if (pMode.toUpperCase().equals("2")) {
                                /**
                                 * Mode 2
                                 */

                                try {
                                    view.showMessage("GIVE NUMBER");
                                    int number = Integer.parseInt(view.getMessage());
                                    boolean IsTheNumberPerfect = theModel.IsPerfect(number);
                                    view.showMessage("MODE 2 OK");
                                    if (IsTheNumberPerfect) {
                                        view.showMessage("Given number is perfect \n");
                                    } else {
                                        view.showMessage("Given number is not perfect \n");
                                    }

                                } catch (NumberFormatException e) {
                                    System.err.println("Wrong number.");
                                } catch (PerfectNumbersException ex) {
                                    System.err.println(ex.getMessage());
                                }
                            }

                        }

                    }

                }
            }
        } catch (IOException ex) {
            Logger.getLogger(ServerController.class.getName()).log(Level.SEVERE, null, ex);

        } catch (Exception e) {
            /**
             * if arguments array is too short program ask user to enter data
             */
            System.err.println(e.getMessage());
        }
    }
}
