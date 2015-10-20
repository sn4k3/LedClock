package com.tiago.LedClock.ClockOptions;


import android.os.Bundle;
import android.support.v4.app.DialogFragment;
import android.support.v4.app.FragmentActivity;


import android.support.v4.app.FragmentTabHost;
import android.view.View;
import com.tiago.LedClock.Components.DatePickerFragment;
import com.tiago.LedClock.Components.TimePickerFragment;
import com.tiago.LedClock.R;

/**
 * Created by Tiago on 15/07/2015.
 */
public class ClockOptionsActivity extends FragmentActivity  {
    private FragmentTabHost mTabHost;

    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.clockoptions);

        mTabHost = (FragmentTabHost)findViewById(android.R.id.tabhost);
        mTabHost.setup(this, getSupportFragmentManager(), R.id.realtabcontent);
        mTabHost.addTab(mTabHost.newTabSpec("datetime").setIndicator("Date/Time"), TabDateTime.class, null);
        mTabHost.addTab(mTabHost.newTabSpec("style").setIndicator("Style"), TabStyle.class, null);
    }

    public void onBtnClicked(View view) {
        switch (view.getId()) {
            case R.id.btnToday:
                TabDateTime.Instance.setNow();
                break;
            case R.id.btnSetDate:
                DialogFragment dateFragment = new DatePickerFragment();
                dateFragment.show(getSupportFragmentManager(), "datePicker");
                break;
            case R.id.btnSetTime:
                DialogFragment timeFragment = new TimePickerFragment();
                timeFragment.show(getSupportFragmentManager(), "timePicker");
                break;
        }
    }
}