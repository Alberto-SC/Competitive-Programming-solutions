import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.net.Socket;
import javax.net.ssl.SSLSocketFactory; 
public class ClienteSSL {
    public static void main(String [] args) throws Exeption{
        SSLSocketFactory cliente = (SSLSocketFactory) SSLSocketFactory.getDefault();
        Socket conexion = cliente.createSocket("localhost",50000);

        DataOutputStream salida = new DataOutputStream(conexion.getOutputStream());
        DataInputStream entrada = new DataInputStream(conexion.getInputStream());

        System.out.println(salida.readDouble());
        salida.writeDouble(123.123);
        salida.close();
        entrada.close();
        conexion.close();
    }
}
