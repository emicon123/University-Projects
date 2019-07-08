/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package Controller;

import Model.MainProcesses;
import java.io.IOException;
import java.util.Scanner;

/**
 *
 * @author Wojciech Szczyrba
 */
public class Program {

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {

        try {
            Controller controller = new ServerController(new MainProcesses());
            controller.start();
        } catch (Exception e) {
            System.err.println(e.getMessage());
        }
    }
}
