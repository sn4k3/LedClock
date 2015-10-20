package com.tiago.LedClock.ClockOptions;

import android.os.Bundle;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.TextView;
import com.tiago.LedClock.Commands;
import com.tiago.LedClock.R;

import java.util.Calendar;

/**
 * Created by Tiago on 15/07/2015.
 */
public class TabDateTime extends android.support.v4.app.Fragment {
    TextView tvDateTime;
    public static int hours;
    public static int minutes;
    public static int seconds;
    public static int day;
    public static int month;
    public static int year;

    public static TabDateTime Instance;

    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container, Bundle savedInstanceState) {

        View view = inflater.inflate(R.layout.tab_datetime, container, false);

        tvDateTime = (TextView)view.findViewById(R.id.tvClockDateTime);
        setNow();

        Instance = this;

        return view;
    }

    public void setNow(){
        Calendar c = Calendar.getInstance();
        hours = c.get(Calendar.HOUR);
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
                Commands.formatTimeDigits(seconds);     // Second
    }


}