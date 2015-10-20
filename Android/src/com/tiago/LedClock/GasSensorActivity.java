package com.tiago.LedClock;

import android.app.Activity;
import android.os.Bundle;
import android.view.View;

/**
 * Created by Tiago on 22/08/2015.
 */
public class GasSensorActivity extends Activity {
    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.gassensor);
    }

    public void onBtnClicked(View view) {
        try
        {
            switch (view.getId()) {
                case R.id.btnGasSensorOn:
                    MyActivity.Instance.sendData(String.format("%s 1", Commands.COMMAND_GASSENSOR_PREFIX));
                    break;
                case R.id.btnGasSensorOff:
                    MyActivity.Instance.sendData(String.format("%s 0", Commands.COMMAND_GASSENSOR_PREFIX));
                    break;
            }
        }
        catch (Exception ignored){}
    }
}