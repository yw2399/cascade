//import util.properties packages
import java.util.Properties;
import java.util.Arrays;
import java.lang.Math;

import io.cascade.*;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.nio.CharBuffer;
import java.nio.charset.Charset;
import java.nio.ByteBuffer;
import java.util.Map;
import java.util.List;


public class Cascade_Writer {
    public final static int KB     = 1024;
    public final static int MB     = 1024 * KB;
    public final static char end_flag     = '$';
    public final static String topicName = "hello";

    public static void main(String[] args) throws Exception{

        Client client = new Client();
        //int[] msg_size = {2, 4, 8, 16, 32, 64, 128, 256, 512, 1024, 2048, 4096, 8*KB, 16*KB, 32*KB, 64*KB, 128*KB, 256*KB, MB/2};
        //int[] msg_size = {1*KB, 100*KB, 200*KB, 300*KB, 400*KB, 500*KB, 600*KB, 700*KB, 800*KB, 900*KB, 1000*KB};
        int[] msg_size = {512};
        long[] duration = new long[msg_size.length];
        for (int i = 0; i < msg_size.length; i++) {
            //duration[i] = new Cascade_Writer().performance_test(client, i*100, 100, msg_size[i]);
            duration[i] = new Cascade_Writer().performance_test(client, i*100, 1, msg_size[i]);
        }
        for (int i = 0; i < msg_size.length; i++){
            System.out.println(duration[i]/100/1000);
        }
        return;
    }

    public String readbuffer(ByteBuffer bb) {
            byte b[] = new byte[bb.capacity()];
            for (int j = 0;j < bb.capacity(); j++){
                b[j] = bb.get(j);
            }
            return new String(b);
    }

    public long performance_test(Client client, int start_key, int message_count,
            int message_size) {
        System.out.printf("Performance test for StartKey: %d, MessageSize: %d.\n", start_key, message_size);

        //Prepare the message.
        byte[][] chars = new byte[message_count][message_size];
        for (int i = 0; i < message_count; i++)
            Arrays.fill(chars[i], (byte)(i%10+48));

        
        ByteBuffer[] bbval_arr = new ByteBuffer[message_count];
        for (int i = 0; i < message_count; i++){
            bbval_arr[i] = ByteBuffer.allocateDirect(message_size); 
            bbval_arr[i].put(chars[i]);
        }
        ByteBuffer[] bbkey_arr = new ByteBuffer[message_count];
        for (int i = 0; i < message_count; i++){
            byte[] key = Integer.toString(start_key+i).getBytes();
            bbkey_arr[i] = ByteBuffer.allocateDirect(key.length); 
            bbkey_arr[i].put(key);
        }
        

        boolean receive_flag = false;
        ServiceType type = ServiceType.VCSS;

        long total_time = 0;
        //Send the message.
        System.out.printf("About to start test.\n");
        for(int i = 0; i < message_count; i++){
            long startTime = System.nanoTime();
            client.put(type, bbkey_arr[i], bbval_arr[i], 0, 0);
            byte[] bk = Integer.toString(start_key + i + 10000).getBytes();
            ByteBuffer bbkey = ByteBuffer.allocateDirect(bk.length);
            bbkey.put(bk);

            //System.out.printf("Reader Key created.\n");
            while(true){
                //Check the last key.
                QueryResults<ByteBuffer> qrb = client.get(type, bbkey, -1, 0, 0);
                //Check if the reading is successful or not.
                Map<Integer, ByteBuffer> data = qrb.get();
                ByteBuffer bb = data.values().iterator().next();
                if (bb.capacity() != 0)
                    break;
            }
            //System.out.printf("Read done.\n");
            long endTime = System.nanoTime();
            total_time += endTime - startTime;
        }

        //System.out.printf("Expecting Key %s.\n", readbuffer(bbkey));
        /*
        //Send the message.
        for(int i = 0; i < message_count; i++){
            //Maximum key is 2000, so 4 digits should suffice.
            //byte[] key = Integer.toString(start_key+i).getBytes();
            //ByteBuffer bbkey = ByteBuffer.allocateDirect(key.length);
            //bbkey.put(key);

            //ByteBuffer bbval = ByteBuffer.allocateDirect(message_size);
            //bbval.put(chars[i]);

            //System.out.printf("Write Key %s with value %s.\n", readbuffer(bbkey), readbuffer(bbval));
            //client.put(type, bbkey, bbval, 0, 0);
            client.put_and_forget(type, bbkey_arr[i], bbval_arr[i], 0, 0);
        }
        // Check if I can get the last value I write.
        //Wait for the reponse from echo server.

        byte[] bk = Integer.toString(start_key + message_count - 1 + 10000).getBytes();
        ByteBuffer bbkey = ByteBuffer.allocateDirect(bk.length);
        bbkey.put(bk);
        //System.out.printf("Expecting Key %s.\n", readbuffer(bbkey));
        while(true){
            //Check the last key.
            QueryResults<ByteBuffer> qrb = client.get(type, bbkey, -1, 0, 0);
            //Check if the reading is successful or not.
            Map<Integer, ByteBuffer> data = qrb.get();
            ByteBuffer bb = data.values().iterator().next();
            if (bb.capacity() != 0)
                break;
        }
        */

        long endTime = System.nanoTime();
        //long duration = (endTime - startTime);  //divide by 1000000 to get milliseconds.
        long duration = total_time;  //divide by 1000000 to get milliseconds.
        System.out.printf("Total time consumption is %d.\n", duration/10/1000);
        return duration;
    }
}
