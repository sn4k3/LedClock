package com.tiago.LedClock;

import android.os.Bundle;
import android.support.v4.app.DialogFragment;
import android.support.v4.app.FragmentActivity;
import android.util.Log;
import android.view.View;
import android.widget.CheckBox;
import android.widget.EditText;
import android.widget.SeekBar;
import android.widget.TextView;

import com.tiago.LedClock.Components.DatePickerFragment;
import com.tiago.LedClock.Components.TimePickerFragment;

import java.util.Calendar;

/**
 * Created by Tiago on 18/08/2015.
 */
public class ClockActivity extends FragmentActivity {
    String TAG = "CLOCK";
    public static int hours;
    public static int minutes;
    public static int seconds;
    public static int day;
    public static int month;
    public static int year;

    TextView tvDateTime;
    EditText timeColors[][];
    EditText etBrightness;
    CheckBox cbBrightness;
    SeekBar sbBrightness;

    public static ClockActivity Instance;

    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.clock);

        tvDateTime = (TextView)findViewById(R.id.tvClockDateTime);
        timeColors = new EditText[3][3];
        timeColors[0][0] = (EditText)findViewById(R.id.etClockTimeColorsHoursRed);
        timeColors[0][1] = (EditText)findViewById(R.id.etClockTimeColorsHoursGreen);
        timeColors[0][2] = (EditText)findViewById(R.id.etClockTimeColorsHoursBlue);
        timeColors[1][0] = (EditText)findViewById(R.id.etClockTimeColorsMinutesRed);
        timeColors[1][1] = (EditText)findViewById(R.id.etClockTimeColorsMinutesGreen);
        timeColors[1][2] = (EditText)findViewById(R.id.etClockTimeColorsMinutesBlue);
        timeColors[2][0] = (EditText)findViewById(R.id.etClockTimeColorsSecondsRed);
        timeColors[2][1] = (EditText)findViewById(R.id.etClockTimeColorsSecondsGreen);
        timeColors[2][2] = (EditText)findViewById(R.id.etClockTimeColorsSecondsBlue);
        etBrightness = (EditText)findViewById(R.id.etClockOptionsBrightness);
        cbBrightness = (CheckBox)findViewById(R.id.chClockOptionsBrightnessAuto);
        sbBrightness = (SeekBar)findViewById(R.id.sbClockOptionsBrightness);
        setNow();

        sbBrightness.setOnSeekBarChangeListener(new SeekBar.OnSeekBarChangeListener() {

            @Override
            public void onStopTrackingTouch(SeekBar seekBar) {
                // TODO Auto-generated method stub
            }

            @Override
            public void onStartTrackingTouch(SeekBar seekBar) {
                // TODO Auto-generated method stub
            }

            @Override
            public void onProgressChanged(SeekBar seekBar, int progress, boolean fromUser) {
                // TODO Auto-generated method stub

                etBrightness.setText(Integer.toString(progress));
            }
        });

        Instance = this;
    }

    public void onBtnClicked(View view) {
        switch (view.getId()) {
            case R.id.btnClockToday:
                setNow();
                break;
            case R.id.btnClockPickDate:
                DialogFragment dateFragment = new DatePickerFragment();
                dateFragment.show(getSupportFragmentManager(), "datePicker");
                break;
            case R.id.btnClockPickTime:
                DialogFragment timeFragment = new TimePickerFragment();
                timeFragment.show(getSupportFragmentManager(), "timePicker");
                break;
            case R.id.btnClockSync:
                MyActivity.Instance.sendData(getCommand());
                break;
            case R.id.btnClockStyleHoursFill:
                MyActivity.Instance.sendData(getCommandStyle('H', (byte) 0));
                break;
            case R.id.btnClockStyleHoursCurrent:
                MyActivity.Instance.sendData(getCommandStyle('H', (byte) 1));
                break;
            case R.id.btnClockStyleHoursNone:
                MyActivity.Instance.sendData(getCommandStyle('H', (byte) 2));
                break;
            case R.id.btnClockStyleMinutesFill:
                MyActivity.Instance.sendData(getCommandStyle('M', (byte) 0));
                break;
            case R.id.btnClockStyleMinutesCurrent:
                MyActivity.Instance.sendData(getCommandStyle('M', (byte) 1));
                break;
            case R.id.btnClockStyleMinutesNone:
                MyActivity.Instance.sendData(getCommandStyle('M', (byte) 2));
                break;
            case R.id.btnClockStyleSecondsFill:
                MyActivity.Instance.sendData(getCommandStyle('S', (byte) 0));
                break;
            case R.id.btnClockStyleSecondsCurrent:
                MyActivity.Instance.sendData(getCommandStyle('S', (byte) 1));
                break;
            case R.id.btnClockStyleSecondsNone:
                MyActivity.Instance.sendData(getCommandStyle('S', (byte) 2));
                break;

            case R.id.btnClockTimeColorsHoursSync:
                MyActivity.Instance.sendData(getCommandColors('H'));
                break;
            case R.id.btnClockTimeColorsMinutesSync:
                MyActivity.Instance.sendData(getCommandColors('M'));
                break;
            case R.id.btnClockTimeColorsSecondsSync:
                MyActivity.Instance.sendData(getCommandColors('S'));
                break;

            case R.id.btnClockOptionsBrightnessSync:
                MyActivity.Instance.sendData(getCommandBrightness());
                break;

            case R.id.btnClockLEDTesterColorWipe:
                MyActivity.Instance.sendData(getCommandLEDTest((byte) 1));
                break;
            case R.id.btnClockLEDTesterRainbow:
                MyActivity.Instance.sendData(getCommandLEDTest((byte) 2));
                break;
            case R.id.btnClockLEDTesterRainbowCycle:
                MyActivity.Instance.sendData(getCommandLEDTest((byte) 3));
                break;
            case R.id.btnClockLEDTesterTheaterChase:
                MyActivity.Instance.sendData(getCommandLEDTest((byte) 4));
                break;
            case R.id.btnClockLEDTesterTheaterChaseRainbow:
                MyActivity.Instance.sendData(getCommandLEDTest((byte) 5));
                break;
            case R.id.btnClockLEDTesterAll:
                MyActivity.Instance.sendData(getCommandLEDTest((byte) 6));
                break;
        }
    }

    public void setNow(){
        Calendar c = Calendar.getInstance();

        hours = c.get(Calendar.HOUR_OF_DAY);
        minutes = c.get(Calendar.MINUTE);
        seconds = c.get(Calendar.SECOND);

        day = c.get(Calendar.DAY_OF_MONTH);
        month = c.get(Calendar.MONTH);
        year = c.get(Calendar.YEAR);

        updateDateTime();
    }

    public void updateDateTime()
    {
        tvDateTime.setText(Commands.formatTimeDigits(day) + "-" + Commands.formatTimeDigits(month) + "-" + year + "  " + Commands.formatTimeDigits(hours) + ":" + Commands.formatTimeDigits(minutes) + ":" + Commands.formatTimeDigits(seconds));
    }

    public String getCommand()
    {

        return Commands.COMMAND_SETTIME_PREFIX+
                Integer.toString(year).substring(2, 4)+ // Year
                Commands.formatTimeDigits(month)+       // Month
                Commands.formatTimeDigits(day)+         // Day
                Commands.formatTimeDigits(hours)+       // Hour
                Commands.formatTimeDigits(minutes)+     // Minute
                Commands.formatTimeDigits(seconds);
    }

    public String getCommandStyle(char hms, byte style)
    {
        return String.format("%s %c %d", Commands.COMMAND_CLOCKSTYLE_PREFIX, hms, style);
    }

    public String getCommandColors(char hms)
    {
        byte index = 0;
        switch (hms)
        {
            case 'h':
            case 'H':
                break;
            case 'm':
            case 'M':
                index = 1;
                break;
            case 's':
            case 'S':
                index = 2;
                break;
        }
        String colorStr = "";
        for (byte i = 0; i < 3; i++)
        {
            String text = timeColors[index][i].getText().toString();
            short value;
            try {
                value = Short.parseShort(text);
                if (value < 0 || value > 255) {
                    timeColors[index][i].setText("0");
                    value = 0;
                }
            }
            catch (Exception ex){
                timeColors[index][i].setText("0");
                value = 0;
            }

            colorStr += String.format(" %s", Short.toString(value));
        }
        return String.format("%s %c%s", Commands.COMMAND_CLOCKCOLOR_PREFIX, hms, colorStr);
    }

    public String getCommandBrightness() {
        short value = 0;
        if(!cbBrightness.isChecked())
        {
            value = (short) sbBrightness.getProgress();
        }
        return String.format("%s %d", Commands.COMMAND_CLOCKBRIGHTNESS_PREFIX, value);
    }

    public String getCommandLEDTest(byte test) {
        return String.format("%s %d", Commands.COMMAND_CLOCKLEDTEST_PREFIX, test);
    }
}