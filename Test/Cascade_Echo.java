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
import java.util.Properties;
import java.util.Arrays;

public class Cascade_Echo {

	public static void main(String[] args) throws Exception {
        Client client = new Client();

        ServiceType type = ServiceType.VCSS;
        //2000 comes from the message we can get from the sender.
        for (int key = 0; key < 2000; key++){
            ByteBuffer bbkey = ByteBuffer.allocateDirect(4);
            bbkey.putInt(key);
            QueryResults<ByteBuffer> qrb = client.get(type, bbkey, 0, 0, 0);
            //TODO: Check if echo receiver gets the correct message.
            Map<Integer, ByteBuffer> data = qrb.get();
	    ByteBuffer bb = data.values().iterator().next();
	    if (bb.capacity() == 0)
		continue;
            ByteBuffer bb_new_key = ByteBuffer.allocateDirect(5);
            bb_new_key.putInt(key+10000);
            //Echo the message back.
            client.put(type, bb_new_key, bb, 0, 0);
        }
        System.out.println("Done echoing.");
    }
}
