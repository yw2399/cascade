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
        System.out.println("Successfully create a client");


        ServiceType type = ServiceType.VCSS;
        int message_count = 1900;
        //2000 comes from the message we can get from the sender.
        ByteBuffer[] bbkey_rec = new ByteBuffer[message_count];
        for (int i = 0; i < message_count; i++){
            byte[] key = Integer.toString(i).getBytes();
            bbkey_rec[i] = ByteBuffer.allocateDirect(key.length); 
            bbkey_rec[i].put(key);
        }
        ByteBuffer[] bbkey_snd = new ByteBuffer[message_count];
        for (int i = 0; i < message_count; i++){
            byte[] key = Integer.toString(10000+i).getBytes();
            bbkey_snd[i] = ByteBuffer.allocateDirect(key.length); 
            bbkey_snd[i].put(key);
        }

        for (int key = 0; key < message_count; key++){
            //System.out.printf("Try key %d\n", key);
            //byte[] bk = Integer.toString(key).getBytes();
            //ByteBuffer bbkey = ByteBuffer.allocateDirect(bk.length);
            //bbkey.put(bk);
            while(true){
                QueryResults<ByteBuffer> qrb = client.get(type, bbkey_rec[key], -1, 0, 0);

                Map<Integer, ByteBuffer> data = qrb.get();
                ByteBuffer bb = data.values().iterator().next();
                if (bb.capacity() == 0)
                    continue;
                else{
                    //int new_key = key+10000;
                    //byte[] new_bk = Integer.toString(new_key).getBytes();
                    //ByteBuffer bb_new_key = ByteBuffer.allocateDirect(new_bk.length);
                    //bb_new_key.put(new_bk);
                    //Echo the message back.
                    //System.out.printf("Send new key %d.\n", new_key);
                    client.put(type, bbkey_snd[key], bb, 0, 0);
                    break;
                }
            }
        }
        System.out.println("Done echoing.");
    }
}
