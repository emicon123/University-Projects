/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package Controller;

import View.ConsoleView;
import java.util.Scanner;

/**
 *
 * @author wojci
 */
public class Program {

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {

        Controller controller = new ClientController(new ConsoleView(), args);

        try {
            /**
             * taking data from arguments
             */
            controller.start();
        } catch (Exception e) {
            /**
             * if arguments array is too short program ask user to enter data
             */
            System.err.println(e.getMessage());
        }
    }
}
