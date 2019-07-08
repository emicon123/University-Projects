/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package pl.polsl.lab.model;

/**
 *
 * @author wojci
 * @version 2.0
 */
public class PerfectNumbersException extends Exception {

    /**
     * Non-parameter constaructor
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
