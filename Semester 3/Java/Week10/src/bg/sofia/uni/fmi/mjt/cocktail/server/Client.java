package bg.sofia.uni.fmi.mjt.cocktail.server;

import java.io.IOException;
import java.net.InetSocketAddress;
import java.nio.ByteBuffer;
import java.nio.channels.SocketChannel;
import java.nio.charset.StandardCharsets;
import java.util.Scanner;

// NIO, blocking
public class Client {

    private static final int SERVER_PORT = 7777;
    private static final String SERVER_HOST = "localhost";
    private static final int BUFFER_SIZE = 1024;

    private static final ByteBuffer BUFFER = ByteBuffer.allocateDirect(BUFFER_SIZE);

    public static void main(String[] args) {

        try (SocketChannel socketChannel = SocketChannel.open();
             Scanner scanner = new Scanner(System.in)) {

            socketChannel.connect(new InetSocketAddress(SERVER_HOST, SERVER_PORT));

            System.out.println("Connected to the server.");

            while (true) {
                System.out.print("Enter message: ");
                String message = scanner.nextLine(); // read a line from the console

                if ("disconnect".equals(message)) {
                    System.out.println("Disconnected from the server");
                    break;
                }

                System.out.println("Sending message <" + message + "> to the server...");

                BUFFER.clear(); // switch to writing mode
                BUFFER.put(message.getBytes()); // buffer fill
                BUFFER.flip(); // switch to reading mode
                socketChannel.write(BUFFER); // buffer drain

                BUFFER.clear(); // switch to writing mode
                socketChannel.read(BUFFER); // buffer fill
                BUFFER.flip(); // switch to reading mode

                byte[] byteArray = new byte[BUFFER.remaining()];
                BUFFER.get(byteArray);
                String reply = new String(byteArray, StandardCharsets.UTF_8); // buffer drain

                // if buffer is a non-direct one, is has a wrapped array, and we can get it
                //String reply = new String(buffer.array(), 0, buffer.position(), "UTF-8"); // buffer drain

                System.out.println(reply);
            }
        } catch (IOException e) {
            throw new RuntimeException("There is a problem with the network communication", e);
        }
    }
}