package pl.polsl.lab.test;

import java.util.Arrays;
import org.junit.Test;
import static org.junit.Assert.*;
import org.junit.Before;
import pl.polsl.lab.model.PerfectNumbersException;
import pl.polsl.lab.model.PerfectNumbersModel;

/**
 *
 * @author Wojciech Szczyrba
 * @version 1.0
 */
public class ModelTest {

    PerfectNumbersModel model;

    //initializing PerfectNumbersModel
    @Before
    public void setup() {
        model = new PerfectNumbersModel();
    }

    //Tests the isPerfect method
    @Test
    public void isPerfectTest() {
        assertTrue(model.isPerfect(6));
        assertTrue(model.isPerfect(28));
        assertFalse(model.isPerfect(1));
        assertFalse(model.isPerfect(0));
        assertFalse(model.isPerfect(27));
        assertFalse(model.isPerfect(-1));
        assertFalse(model.isPerfect(-213));
    }
    
    //Tests the nthPerfectNumber method with unsettled arguments
    @Test
    public void nthPerfectNumberTestWithoutSetArgs() {
        try {
            model.nthPerfectNumber();
            fail("An exception should be thrown when occurs invalid value");
        } catch (PerfectNumbersException e) {
        }
    }

    //Tests the nthPerfectNumber method
    @Test
    public void nthPerfectNumberTest() {
        model.setNthPN(1);
        try {
            model.nthPerfectNumber();
        } catch (PerfectNumbersException e) {
        }
        assertEquals(model.getNthPNResult(), 6);

        model.setNthPN(2);
        try {
            model.nthPerfectNumber();
        } catch (PerfectNumbersException e) {
        }
        assertEquals(model.getNthPNResult(), 28);

        model.setNthPN(3);
        try {
            model.nthPerfectNumber();
        } catch (PerfectNumbersException e) {
        }
        assertEquals(model.getNthPNResult(), 496);

    }

    //Tests the nthPerfectNumber method with exception
    @Test
    public void nthPerfectNumberTestException() {
        model.setNthPN(0);
        try {
            model.nthPerfectNumber();
            fail("An exception should be thrown when occurs invalid value");
        } catch (PerfectNumbersException e) {
        }

        model.setNthPN(-50);
        try {
            model.nthPerfectNumber();
            fail("An exception should be thrown when occurs invalid value");
        } catch (PerfectNumbersException e) {
        }
    }

    //Tests the checkingPNInTheRange method with unsettled arguments
    @Test
    public void checkingPNInTheRangeTestWithoutSetArgs() {
        try {
            model.checkingPNInTheRange();
            fail("An exception should be thrown when the arguments have not been set");
        } catch (PerfectNumbersException e) {
        }
    }

    //Tests the checkingPNInTheRangee method
    @Test
    public void checkingPNInTheRangeTest() {
        model.setMinRange(10);
        model.setMaxRange(30);
        try {
            model.checkingPNInTheRange();
        } catch (PerfectNumbersException e) {
        }
        int[] expectedResult = new int[]{28};
        int[] result = model.getArrayOfPN().stream().mapToInt(Integer::intValue).toArray();
        assertTrue(Arrays.equals(result, expectedResult));

        model.setMinRange(1);
        model.setMaxRange(1000);
        try {
            model.checkingPNInTheRange();
        } catch (PerfectNumbersException e) {
        }
        expectedResult = new int[]{6, 28, 496};
        result = model.getArrayOfPN().stream().mapToInt(Integer::intValue).toArray();
        assertTrue(Arrays.equals(result, expectedResult));

        model.setMinRange(-20);
        model.setMaxRange(30);
        try {
            model.checkingPNInTheRange();
        } catch (PerfectNumbersException e) {
        }
        expectedResult = new int[]{6, 28};
        result = model.getArrayOfPN().stream().mapToInt(Integer::intValue).toArray();
        assertTrue(Arrays.equals(result, expectedResult));

    }

    //Tests the checkingPNInTheRange method with exception
    @Test
    public void checkingPNInTheRangeTestException() {
        model.setMinRange(60);
        model.setMaxRange(30);
        try {
            model.checkingPNInTheRange();
            fail("An exception should be thrown when occurs invalid value");
        } catch (PerfectNumbersException e) {
        }
    }
}
