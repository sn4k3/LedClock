package com.tiago.LedClock;

import android.app.Activity;
import android.bluetooth.BluetoothAdapter;
import android.bluetooth.BluetoothDevice;
import android.bluetooth.BluetoothSocket;
import android.content.Intent;
import android.os.Bundle;
import android.util.Log;
import android.view.Menu;
import android.view.MenuInflater;
import android.view.MenuItem;
import android.view.View;
import android.widget.TextView;
import android.widget.Toast;

import com.tiago.LedClock.ClockOptions.ClockOptionsActivity;

import java.io.IOException;
import java.io.OutputStream;
import java.util.Set;
import java.util.UUID;

public class MyActivity extends Activity {
    public static MyActivity Instance;

    private static final String TAG = "LEDCLOCK";

    TextView text;

    private BluetoothAdapter btAdapter = null;
    private BluetoothSocket btSocket = null;
    private OutputStream outStream = null;


    // Intent request codes
    private static final int REQUEST_CONNECT_DEVICE_SECURE = 1;
    private static final int REQUEST_ENABLE_BT = 3;

    // Well known SPP UUID
    private static final UUID MY_UUID = UUID.fromString("00001101-0000-1000-8000-00805F9B34FB");

    // Insert your bluetooth devices MAC address
    private static String address = "98:D3:31:70:3A:FA";

    /** Called when the activity is first created. */
    @Override
    public void onCreate(Bundle savedInstanceState) {
        Instance = this;
        super.onCreate(savedInstanceState);

        setContentView(R.layout.main);
        text = (TextView) findViewById(R.id.textEdit);

        btAdapter = BluetoothAdapter.getDefaultAdapter();

        checkBTState();

        Set<BluetoothDevice> pairedDevices = btAdapter.getBondedDevices();

//    if (pairedDevices.size() > 0) {
//       for (BluetoothDevice device : pairedDevices) {
//    	
//        String deviceBTName = device.getName();
//        text.setText(text.getText() + " Device: " + deviceBTName);
//        if (deviceBTName.equals("HC-06")){
//        	address = device.getAddress();
//        }
//       }
//   }
    }
  
  /*public void ledOn(View v){
	  sendData("1");
      Toast msg = Toast.makeText(getBaseContext(), "LED is ON", Toast.LENGTH_SHORT);
      msg.show();
  }
  
  public void ledOff(View v){
	  sendData("0");
      Toast msg = Toast.makeText(getBaseContext(), "LED is OFF", Toast.LENGTH_SHORT);
      msg.show();
  }*/

    public void onBtnClicked(View view) {
        Intent intent;
        switch (view.getId()) {
            case R.id.btnClockOptions:
                intent = new Intent(this, ClockActivity.class);
                startActivity(intent);
                break;
            case R.id.btnRadio:
                intent = new Intent(this, RadioActivity.class);
                startActivity(intent);
                break;
            case R.id.btnGasSensor:
                intent = new Intent(this, GasSensorActivity.class);
                startActivity(intent);
                break;
        }
    }

    public void ledToggle(View v){
        android.widget.Button myButton = (android.widget.Button)findViewById(v.getId());
        Log.d(TAG, myButton.getHint().toString());
        sendData("TOGGLE LED " + myButton.getHint().toString());
    }


    public void connectToDevice(String adr) {
        super.onResume();


        // Set up a pointer to the remote node using it's address.
        BluetoothDevice device = btAdapter.getRemoteDevice(adr);

        // Two things are needed to make a connection:
        //   A MAC address, which we got above.
        //   A Service ID or UUID.  In this case we are using the
        //     UUID for SPP.
        try {
            btSocket = device.createRfcommSocketToServiceRecord(MY_UUID);
        } catch (IOException e) {
            errorExit("Fatal Error", "In onResume() and socket create failed: " + e.getMessage() + ".");
        }

        // Discovery is resource intensive.  Make sure it isn't going on
        // when you attempt to connect and pass your message.
        btAdapter.cancelDiscovery();

        // Establish the connection.  This will block until it connects.
        try {
            btSocket.connect();
        } catch (IOException e) {
            try {
                btSocket.close();
            } catch (IOException e2) {
                errorExit("Fatal Error", "In onResume() and unable to close socket during connection failure" + e2.getMessage() + ".");
            }
        }

        // Create a data stream so we can talk to server.
        try {
            outStream = btSocket.getOutputStream();
        } catch (IOException e) {
            errorExit("Fatal Error", "In onResume() and output stream creation failed:" + e.getMessage() + ".");
        }

    }

//  @Override
//  public void onPause() {
//    super.onPause();
//
////    if (outStream != null) {
////      try {
////        outStream.flush();
////      } catch (IOException e) {
////        errorExit("Fatal Error", "In onPause() and failed to flush output stream: " + e.getMessage() + ".");
////      }
////    }
//
//    try     {
//      btSocket.close();
//    } catch (IOException e2) {
//      errorExit("Fatal Error", "In onPause() and failed to close socket." + e2.getMessage() + ".");
//    }
//  }

    private void checkBTState() {
        // Check for Bluetooth support and then check to make sure it is turned on

        // Emulator doesn't support Bluetooth and will return null
        if(btAdapter==null) {
            errorExit("Fatal Error", "Bluetooth Not supported. Aborting.");
        } else {
            if (btAdapter.isEnabled()) {
                Log.d(TAG, "...Bluetooth is enabled...");
            } else {
                //Prompt user to turn on Bluetooth
                Intent enableBtIntent = new Intent(btAdapter.ACTION_REQUEST_ENABLE);
                startActivityForResult(enableBtIntent, REQUEST_ENABLE_BT);
            }
        }
    }

    private void errorExit(String title, String message){
        Toast msg = Toast.makeText(getBaseContext(), title + " - " + message, Toast.LENGTH_SHORT);
        msg.show();
        finish();
    }

    public void sendData(String message) {
        Log.d("CMD", message);
        byte[] msgBuffer = message.getBytes();
        try {
            outStream.write(msgBuffer);
        } catch (IOException e) {
            String msg = "In onResume() and an exception occurred during write: " + e.getMessage();
            errorExit("Fatal Error", msg);
        }
    }

    public void onActivityResult(int requestCode, int resultCode, Intent data) {
        switch (requestCode) {
            case REQUEST_CONNECT_DEVICE_SECURE:
                // When DeviceListActivity returns with a device to connect
                if (resultCode == Activity.RESULT_OK) {
                    connectDevice(data, true);
                }
                break;
        }
    }

    private void connectDevice(Intent data, boolean secure) {
        // Get the device MAC address
        address = data.getExtras().getString(DeviceListActivity.EXTRA_DEVICE_ADDRESS);
        text.setText("Device Address: " + address);
        connectToDevice(address);
        // Get the BluetoothDevice object
        BluetoothDevice device = btAdapter.getRemoteDevice(address);
    }


    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        MenuInflater inflater = getMenuInflater();
        inflater.inflate(R.menu.option_menu, menu);
        return true;
    }
    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        Intent serverIntent = null;
        switch (item.getItemId()) {
            case R.id.secure_connect_scan:
                // Launch the DeviceListActivity to see devices and do scan
                serverIntent = new Intent(this, DeviceListActivity.class);
                startActivityForResult(serverIntent, REQUEST_CONNECT_DEVICE_SECURE);
                return true;
        }
        return false;
    }
}