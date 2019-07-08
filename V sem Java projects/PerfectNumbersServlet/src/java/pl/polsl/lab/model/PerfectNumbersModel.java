package pl.polsl.lab.model;

// packages containing class definitions 
import java.util.ArrayList;
import java.util.Hashtable;
import java.util.List;

/**
 * A class that performs calculations on primary numbers
 *
 * @author wojci
 * @version 2.0
 */
public class PerfectNumbersModel {

    // beginning of the range 
    private int minRange;
    // end of range
    private int maxRange;
    // number representing potential perfect number
    private int number;
    // nth perfect number
    private int nthPN;
    // number representing result of nth perfect number to check
    private int nthPNResult;
    // typically a secure class of objects containing range of perfect numbers
    private List<Integer> listOfPN;
    // collection stores data
    private Hashtable<String, String> stats;

    // specification of the lambda expression with two parameters
    interface IntegerMath {

        boolean operation(int a, int b);
    }

    //implements of the lambda expression
    IntegerMath range = (a, b) -> {
        if ((a - b) < 0) {
            return false;
        }
        return true;
    };

    //constructor
    public PerfectNumbersModel() {
        stats = new Hashtable<String, String>();
    }

    /**
     * Function to check if given number is perfect,
     *
     * @param number given number,
     * @return boolean value - number is perfect or not
     */
    public boolean isPerfect(int number) {

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
            return false;
        }
    }

    /**
     * Sets the perfect numbers in the given range
     *
     * @throws PerfectNumbersException - own defined exception thrown when
     * occurs invalid range
     */
    @SuppressWarnings("unchecked")
    public void checkingPNInTheRange() throws PerfectNumbersException {

        //if first value of range is greater than second value throw an own exception
        //using lambda expression
        if ((range.operation(this.minRange, this.maxRange))) {
            throw new PerfectNumbersException("Invalid range");
        }

        //list to store perfect numbers
        listOfPN = new ArrayList();

        for (int num = this.minRange; num < this.maxRange; num++) {
            if (isPerfect(num)) {
                listOfPN.add(num);
            }

        }

    }

    /**
     * Sets nth perfect number
     *
     * @throws PerfectNumbersException - own defined exception thrown when value
     * is less than 1
     */
    public void nthPerfectNumber() throws PerfectNumbersException {

//value representing the nth perfect number
        int counter = this.nthPN;
        //if value is incorrect throw an own exception
        if (counter < 1) {
            throw new PerfectNumbersException("Invalid nth perfect number");
        }
        //value representing first perfect number
        int num = 1;
        while (counter > 0) {
            if (isPerfect(num)) {
                counter--;
            }
            num++;
        }
        //if counter=0 the nth perfect number is num minus 1
        this.nthPNResult = --num;
    }

    /**
     * Sets the value of the private field "minRange"
     *
     * @param minRange - containing the value of nthPN
     */
    public void setMinRange(int minRange) {
        this.minRange = minRange;
    }

    /**
     * Sets the value of the private field "maxRange"
     *
     * @param maxRange - containing the value of maxRange
     */
    public void setMaxRange(int maxRange) {
        this.maxRange = maxRange;
    }

    /**
     * Returns the value of the private field "minRange"
     *
     * @return int containing the value of the private field in the
     * {@link PerfectNumbersModel}.
     */
    public int getMinRange() {
        return minRange;
    }

    /**
     * Returns the value of the private field "maxRange"
     *
     * @return int containing the value of the private field in the
     * {@link PerfectNumbersModel}.
     */
    public int getMaxRange() {
        return maxRange;
    }

    /**
     * Sets the value of the private field "number"
     *
     * @param number - containing the value of number
     */
    public void setNumber(int number) {
        this.number = number;
    }

    /**
     * Returns the value of the private field "number"
     *
     * @return int containing the value of the private field in the
     * {@link PerfectNumbersModel}.
     */
    public int getNumber() {
        return number;
    }

    /**
     * Sets the value of the private field "nthPN"
     *
     * @param nthPN - containing the value of nthPN
     */
    public void setNthPN(int nthPN) {
        this.nthPN = nthPN;
    }

    /**
     * Returns the value of the private field "nthPN"
     *
     * @return int containing the value of the private field in the
     * {@link PerfectNumbersModel}.
     */
    public int getNthPN() {
        return nthPN;
    }

    /**
     * Returns the value of the private field "nthPNResult"
     *
     * @return int containing the value of the private field in the
     * {@link PerfectNumbersModel}.
     */
    public int getNthPNResult() {
        return nthPNResult;
    }

    /**
     * Returns the array of the private field "listOfPN"
     *
     * @return array containing the values of the private field in the
     * {@link PerfectNumbersModel}.
     */
    public List<Integer> getArrayOfPN() {
        return listOfPN;
    }

    /**
     * Returns the Hashtable of statistics
     *
     * @return history of range perfect numbers
     */
    public Hashtable<String, String> getStats() {
        return stats;
    }

    /**
     * Puts two string into Hashtable of history calculate
     *
     * @param key range
     * @param value perfect numbers in range
     */
    public void putStats(String key, String value) {
        stats.put(key, value);
    }

}
