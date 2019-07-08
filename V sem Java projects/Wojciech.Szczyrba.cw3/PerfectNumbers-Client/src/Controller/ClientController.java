/*
 * To change this license header, mode License Headers in Project Properties.
 * To change this template file, mode Tools | Templates
 * and open the template in the editor.
 */
package Controller;

import Model.ConnectionErrorException;
import View.View;
import java.io.BufferedReader;
import java.io.DataOutputStream;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.net.*;
import java.util.ArrayList;

/**
 *
 * @author wojci
 */
public class ClientController implements Controller {

    private View theView;
    String[] inputArgs;

    /**
     * Initial method.
     *
     * @param view , View instance
     * @param args , string array, values of console arguments
     */
    public ClientController(View view, String[] args) {
        this.theView = view;
        this.inputArgs = args;

    }

    /**
     * Method start controller.
     */
    @Override()
    public void start() {

        //theView.PNView();
        int mode = 0;
        //boolean error = false;
        String buffer = "";

        //
        int number = 0;
        int minRange = 0;
        int maxRange = 0;

        try {
            /**
             * taking data from arguments
             */

            this.theView.showMessage("Choose arguments.\n");
            mode = Integer.parseInt(this.inputArgs[0]);

        } catch (ArrayIndexOutOfBoundsException e) {
            /**
             * if arguments array is too short program ask user to enter data
             */
            this.theView.showMessage("Arguments are not correct.\n");

            mode = Integer.parseInt(this.theView.getMessage("Type which mode you want to choose (1/2)\n 1. Generating perfect numbers in the range \n 2. Checking if given number is perfect. \n Type: "));

        } finally {
            /**
             * create Corrector instance and call replace method
             */

            try {
                Socket clientSocket = new Socket();
                clientSocket.connect(new InetSocketAddress("localhost", 8888));
                PrintWriter toServer = new PrintWriter(clientSocket.getOutputStream(), true);
                BufferedReader fromServer = new BufferedReader(new InputStreamReader(clientSocket.getInputStream()));

                if (!(buffer = fromServer.readLine()).toUpperCase().equals("HELLO")) {
                    throw new ConnectionErrorException("Wystąpił błąd podczas połączenia z serwerem!");
                }

                toServer.println("MODE");
                toServer.flush();
                if ((buffer = fromServer.readLine()).toUpperCase().equals("GIVE ME PROGRAM MODE")) {
                    toServer.println(mode);
                } else {
                    throw new ConnectionErrorException("An error occured when connecting to the server!");
                }

                if (!(buffer = fromServer.readLine()).toUpperCase().equals("OK MODE")) {
                    throw new ConnectionErrorException("An error occured when connecting to the server!");
                }
                toServer.println("PROCEED");

                if ((buffer = fromServer.readLine()).toUpperCase().equals("PROCEEDING")) {

                    if ((buffer = fromServer.readLine()).toUpperCase().equals("GIVE ME MINIMUM RANGE")) {

                        this.theView.showMessage("Type the minimum range value: ");
                        try {

                            minRange = Integer.parseInt(this.inputArgs[1]);

                            toServer.println(minRange);

                        } catch (ArrayIndexOutOfBoundsException e) {
                            /**
                             * if arguments array is too short program ask user
                             * to enter data
                             */
                            this.theView.showMessage("Arguments are not correct.\n");

                            minRange = Integer.parseInt(this.theView.getMessage("Type the minimum range value: "));
                            toServer.println(minRange);
                        } finally {
                            if ((buffer = fromServer.readLine()).toUpperCase().equals("GIVE ME MAXIMUM RANGE")) {
                                this.theView.showMessage("Type the maximum range value: ");
                                try {

                                    maxRange = Integer.parseInt(this.inputArgs[2]);

                                    toServer.println(maxRange);

                                } catch (ArrayIndexOutOfBoundsException e) {
                                    /**
                                     * if arguments array is too short program
                                     * ask user to enter data
                                     */
                                    this.theView.showMessage("Arguments are not correct.\n");

                                    maxRange = Integer.parseInt(this.theView.getMessage("Type the maximum range value: "));
                                    toServer.println(maxRange);
                                } finally {
                                    if ((buffer = fromServer.readLine()).toUpperCase().equals("MODE 1 OK")) {

                                        this.theView.showMessage("Perfect numbers in the range are: ");

                                        String mode1Answer = fromServer.readLine();
                                        this.theView.showMessage(mode1Answer);
                                        this.theView.showMessage("\nOperation mode 1 successfull");
                                    }
                                }
                            }

                        }
                    } else if (buffer.equals("GIVE NUMBER")) {

                        this.theView.showMessage("Type the number to check: ");
                        try {

                            number = Integer.parseInt(this.inputArgs[1]);
                            toServer.println(number);

                        } catch (ArrayIndexOutOfBoundsException e) {
                            /**
                             * if arguments array is too short program ask user
                             * to enter data
                             */
                            this.theView.showMessage("Arguments are not correct.\n");

                            number = Integer.parseInt(this.theView.getMessage("Type the number to check: "));
                            toServer.println(number);
                        } finally {

                            if ((buffer = fromServer.readLine()).toUpperCase().equals("MODE 2 OK")) {

                                String mode2Answer = fromServer.readLine();
                                this.theView.showMessage(mode2Answer);
                                this.theView.showMessage("\nOperation mode 2 successfull");
                            }
                        }
                    } else if (buffer.equals("ERROR")) {
                        this.theView.showMessage("Incorrent mode, quitting server!");
                    }

                } else {
                    throw new ConnectionErrorException("An error occured when connecting to the server!");
                }

                toServer.println("QUIT");

            } catch (ConnectionErrorException ex) {
                this.theView.showError(ex.getMessage());
            } catch (Exception e) {
                this.theView.showError(e.getMessage());
            }

        }

    }

}
