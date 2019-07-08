/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package Model;

import java.util.ArrayList;
import java.util.List;

/**
 * Interface define methods, which Model classes have to have.
 *
 * @author wojci
 */
public interface Model {

    /**
     * Function to find all PN in given range
     *
     * @param minRangeValue minimum value of the range
     * @param maxRangeValue maximum value of the range
     * @return list of PN
     * @throws PerfectNumbersException when numbers are wrong
     */
    public List<Integer> checkingPNInTheRange(int minRangeValue, int maxRangeValue) throws PerfectNumbersException;


    /**
     * Function to check if given number is perfect,
     *
     * @param number given number,
     * @return boolean value - number is perfect or not
     * @throws PerfectNumbersException when number is wrong
     */
    boolean IsPerfect(int number) throws PerfectNumbersException;
}
