/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package View;

import java.util.List;
import java.util.Scanner;

/**
 *
 * @author wojci
 */
public class ConsoleView implements View {

    Scanner scanner;

    public ConsoleView() {
        this.scanner = new Scanner(System.in);
    }

    @Override
    public void showMessage(String message) {
        System.out.printf(message);
    }

    @Override
    public String getMessage(String message) {
        this.showMessage(message);
        String backMessage = scanner.nextLine();
        return backMessage;
    }

    @Override
    public void showError(String error) {
        System.err.printf(error);
    }

}
