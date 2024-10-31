
import java.io.InputStream;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.util.Properties;

public class GetProperties {
    /**
     * 
     * @param filename
     * @return String[] {url, user, password}
     */
    static String[] getProperties(String filename) {
        Properties envProperties = new Properties();
        try (InputStream input = new FileInputStream(filename)) {
            envProperties.load(input);
            String url = envProperties.getProperty("db.uri");
            String user = envProperties.getProperty("db.user");
            String password = envProperties.getProperty("db.password");
            return new String[] { url, user, password };
        } catch (FileNotFoundException e) {
            System.err.println(filename + " file not found");
            e.printStackTrace();
        } catch (IOException e) {
            System.err.println(
                    "Something went wrong with reading environment variables.\nPlease check your "
                            + filename + " file");
            e.printStackTrace();
        }
        return null;
    }
}
