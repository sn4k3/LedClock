package com.tiago.LedClock;

import android.app.Activity;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.CheckBox;
import android.widget.CompoundButton;
import android.widget.EditText;
import android.widget.SeekBar;
import android.widget.TextView;

/**
 * Created by Tiago on 14/08/2015.
 */
public class RadioActivity extends Activity {
    final byte volumeIncrements = 2;
    final short maxVolume = 150;
    int volume = 0;
    TextView tvRadioVolume;
    SeekBar sbRadioVolume;
    CheckBox cbRadioMute;
    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.radio);
        sbRadioVolume = (SeekBar)findViewById(R.id.sbRadioVolume);
        tvRadioVolume = (TextView)findViewById(R.id.tvRadioVolume);
        cbRadioMute = (CheckBox)findViewById(R.id.cbRadioMute);
        volume = sbRadioVolume.getProgress();

        sbRadioVolume.setOnSeekBarChangeListener(new SeekBar.OnSeekBarChangeListener() {

            @Override
            public void onStopTrackingTouch(SeekBar seekBar) {
                volume = seekBar.getProgress();
                setVolume(volume);
                MyActivity.Instance.sendData(Commands.COMMAND_RADIO_PREFIX + " VOL " + Integer.toString(volume));
            }

            @Override
            public void onStartTrackingTouch(SeekBar seekBar) {
                // TODO Auto-generated method stub
            }

            @Override
            public void onProgressChanged(SeekBar seekBar, int progress, boolean fromUser) {
                volume = seekBar.getProgress();
                setVolume(volume);
            }
        });

        cbRadioMute.setOnCheckedChangeListener(new CompoundButton.OnCheckedChangeListener() {
               @Override
               public void onCheckedChanged(CompoundButton buttonView, boolean isChecked) {
                   MyActivity.Instance.sendData(Commands.COMMAND_RADIO_PREFIX + " MUTE " + (isChecked ? "1" : "0"));
               }
           }
        );
    }

    public void onBtnClicked(View v){
        try
        {
            EditText editText = (android.widget.EditText)findViewById(R.id.tbRadioFreq);
            TextView textView = (android.widget.TextView)findViewById(R.id.tvRadioFrequency);
            android.widget.Button myButton = (android.widget.Button) findViewById(v.getId());
            String hint = myButton.getHint().toString();
            if(v.getId() == R.id.btnRadioChange)
            {

                String text = editText.getText().toString();
                int frequency = Integer.parseInt(text);
                if(frequency < 10) return;
                MyActivity.Instance.sendData(Commands.COMMAND_RADIO_PREFIX+" FREQ " + Integer.toString(frequency));
                float frequencyDecimal = (float)frequency / 100;
                textView.setText(Float.toString(frequencyDecimal)+" MHz");
            }
            else {
                MyActivity.Instance.sendData(Commands.COMMAND_RADIO_PREFIX +" "+ hint);
                if(hint.startsWith("FREQ")) {
                    int frequency = Integer.parseInt(myButton.getHint().toString().substring(5));
                    float frequencyDecimal = (float)frequency / 100;
                    editText.setText(Integer.toString(frequency));
                    textView.setText(Float.toString(frequencyDecimal)+" MHz");
                }
                else if(hint.startsWith("VOL -")) {
                    volume = Math.max(0, volume-volumeIncrements);
                    setVolume(volume);
                }
                else if(hint.startsWith("VOL +")) {
                    volume = Math.min(maxVolume, volume + volumeIncrements);
                    setVolume(volume);
                }
            }
        }
        catch (Exception ignored){}

    }

    void setVolume(int volume)
    {
        sbRadioVolume.setProgress(volume);
        int volumePercent = (volume * 100 / maxVolume);
        tvRadioVolume.setText("Volume: ("+Integer.toString(volumePercent)+")");
    }
}