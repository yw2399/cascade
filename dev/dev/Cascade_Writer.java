//import util.properties packages
import java.util.Properties;
import java.util.Arrays;
import java.lang.Math;

import io.cascade.*;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
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
        int[] msg_size = {2, 4, 8, 16, 32, 64, 128, 256, 512, 1024, 2048, 4096, 8*KB, 16*KB, 32*KB, 64*KB, 128*KB, 256*KB, MB/2};
        long[] duration = new long[msg_size.length];
        for (int i = 0; i < msg_size.length; i++) {
            duration[i] = new Cascade_Writer().performance_test(client, i*100, 100, msg_size[i]);
        }
        for (int i = 0; i < msg_size.length; i++){
            System.out.println(duration[i]/100/1000);
        }
        return;
    }

    public long performance_test(Client client, int start_key, int message_count,
                                 int message_size) {
        System.out.printf("Performance test for StartKey: %d, MessageSize: %d.\n", start_key, message_size);

        //Prepare the message.
        byte[][] chars = new byte[message_count][message_size];
        for (int i = 0; i < message_count; i++)
            Arrays.fill(chars[i], (byte)(i%10+48));

        boolean receive_flag = false;
        ServiceType type = ServiceType.VCSS;

        long startTime = System.nanoTime();
        //Send the message.
        for(int i = 0; i < message_count; i++){
            //Maximum key is 2000, so 4 digits should suffice.
            ByteBuffer bbkey = ByteBuffer.allocateDirect(4);
            bbkey.putInt(i);
            ByteBuffer bbval = ByteBuffer.allocateDirect(message_size);
            bbval.put(chars[i]);
            client.put(type, bbkey, bbval, 0, 0);
        }
        while(true){
	    //Check the last key.
            ByteBuffer bbkey = ByteBuffer.allocateDirect(5);
            bbkey.putInt(start_key + message_count - 1 + 10000);
            QueryResults<ByteBuffer> qrb = client.get(type, bbkey, 0, 0, 0);
            //Check if the reading is successful or not.
            Map<Integer, ByteBuffer> data = qrb.get();
	    ByteBuffer bb = data.values().iterator().next();
	    if (bb.capacity() != 0)
		break;
        }

        long endTime = System.nanoTime();
        long duration = (endTime - startTime);  //divide by 1000000 to get milliseconds.
        System.out.printf("Total time consumption is %d.\n", duration);
        return duration;
    }
}
