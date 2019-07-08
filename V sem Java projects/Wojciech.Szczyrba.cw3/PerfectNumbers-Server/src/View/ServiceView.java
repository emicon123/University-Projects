package View;

import View.View;
import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.Closeable;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.io.PrintWriter;
import java.net.Socket;
import java.util.ArrayList;
import java.util.List;

public class ServiceView implements Closeable, View {

    /**
     * socket representing connection to the client
     */
    private Socket socket;
    /**
     * buffered input character stream
     */
    private BufferedReader input;
    /**
     * Formatted output character stream
     */
    private PrintWriter output;

    /**
     * The constructor of instance of the SingleService class. Use the socket as
     * a parameter.
     *
     * @param socket socket representing connection to the client
     */
    public ServiceView(Socket socket) throws IOException {
        this.socket = socket;
        output = new PrintWriter(
                new BufferedWriter(
                        new OutputStreamWriter(
                                socket.getOutputStream())), true);
        input = new BufferedReader(
                new InputStreamReader(
                        socket.getInputStream()));
    }

    @Override
    public void close() throws IOException {
        if (socket != null) {
            socket.close();
        }
    }

    @Override
    public void showMessage(String message) {
        output.println(message);
    }

    @Override
    public String getMessage() {
        try {
            return input.readLine();
        } catch (Exception e) {
            output.println("Closing");
            try {
                socket.close();
            } catch (IOException ex) {
                System.err.println(ex.getMessage());
            }
            return "ERROR";
        }
    }

    @Override
    public void showError(String error) {
        output.println("Error: " + error);
    }

    /**
     * function using for-each statement to print the PN in the range
     *
     * @param l list of PN return String of joined list elements
     */
    @Override
    public String printList(List<Integer> l) {

        //l.forEach(n->System.out.println(n));
        List<String> tmp = new ArrayList<>();
        String a;

        for (int x : l) {
            a = Integer.toString(x);
            tmp.add(a);
        }

        String joined = String.join(", ", tmp);

        return joined;
    }
}
