package test;

/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
//import Model.MainProcesses.*;
import Model.PerfectNumbersException;
import java.util.ArrayList;
import org.junit.*;
import static org.junit.Assert.*;
import static org.hamcrest.CoreMatchers.*;

/**
 *
 * @author wojci
 */
public class Test {

    Model.MainProcesses theModel = new Model.MainProcesses();

    @Before
    public void setup() {

    }

    @org.junit.Test
    public void IsPerfect() {
        try {
            assertTrue(theModel.IsPerfect(6));
            theModel.IsPerfect(-1);
            theModel.IsPerfect(0);
            fail("An exception should be thrown when the amount is non-positive");
        } catch (PerfectNumbersException ex) {
        }

    }

    @org.junit.Test
    public void checkingPNInTheRangeTest() {
        try {
            theModel.checkingPNInTheRange(1, 1000);
            theModel.checkingPNInTheRange(0, 0);
            theModel.checkingPNInTheRange(-1, -1);
            theModel.checkingPNInTheRange(-1, 1);
            theModel.checkingPNInTheRange(1, -1);
            theModel.checkingPNInTheRange(2, 1);
            fail("An ex should be thrown");
        } catch (PerfectNumbersException ex) {
        }
    }
}
