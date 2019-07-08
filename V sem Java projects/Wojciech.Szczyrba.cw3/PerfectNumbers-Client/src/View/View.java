/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package View;

import java.util.List;

/**
 * Interface define methods, which View classes have to have.
 *
 * @author wojci
 */
public interface View {

    /**
     * Method send message on output.
     *
     * @param message string value, value will be send
     */
    public void showMessage(String message);

    /**
     * Method Show message and wait for answer.
     *
     * @param message string value, value will be send
     * @return string value, value from input
     */
    public String getMessage(String message);

    /**
     * Method send error on output.
     *
     * @param error string value, value will be send
     */
    public void showError(String error);

}
