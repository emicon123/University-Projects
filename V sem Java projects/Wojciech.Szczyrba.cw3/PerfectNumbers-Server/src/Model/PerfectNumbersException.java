/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package Model;

/**
 *
 * @author wojci
 */
public class PerfectNumbersException extends Exception {

    /**
     * Non-parameter constructor
     */
    public PerfectNumbersException() {
    }

    /**
     * Constructor
     *
     * @param message display message
     */
    public PerfectNumbersException(String message) {
        super(message);
    }
}
