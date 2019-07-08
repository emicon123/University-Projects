/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package Model;

import java.util.ArrayList;
import java.util.List;

/**
 *
 * @author kamil
 */
public class MainProcesses implements Model {

    /**
     * Function to find all PN in given range
     *
     * @param minRangeValue minimum value of the range
     * @param maxRangeValue maximum value of the range
     * @return list of PN
     * @throws PerfectNumbersException when numbers are wrong
     */
    @Override
    public List<Integer> checkingPNInTheRange(int minRangeValue, int maxRangeValue) throws PerfectNumbersException {

        List<Integer> listOfPN = new ArrayList<>();

        if (minRangeValue < 1 || maxRangeValue < 1) {
            throw new PerfectNumbersException("Numbers in the range have to be greater than 0!");

        } else if (maxRangeValue < minRangeValue) {
            throw new PerfectNumbersException("Maximum value must be greater than minimum value");
        } else {

            //System.out.println("Perfect numbers in the range are:");
            int sum = 0;
            for (int num = minRangeValue; num < maxRangeValue; num++) {
                for (int i = 1; i < num; i++) {
                    if (num % i == 0) {
                        sum += i;
                    }
                }
                if (sum == num) {
                    listOfPN.add(num);
                }
                sum = 0;
            }

        }
        return listOfPN;
    }

    /**
     * Function to check if given number is perfect,
     *
     * @param number given number,
     * @return boolean value - number is perfect or not
     * @throws PerfectNumbersException when number is wrong
     */
    @Override
    public boolean IsPerfect(int number) throws PerfectNumbersException {

        if (number > 1) {

            int sum = 0;

            for (int i = 1; i < number; i++) {
                if (number % i == 0) {
                    sum += i;

                }
            }

            if (sum == number) {
                return true;
            } else {
                return false;
            }
        } else {
            throw new PerfectNumbersException("The number has to be greater than 0!");
        }
    }
}
