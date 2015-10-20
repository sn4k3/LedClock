package com.tiago.LedClock;

/**
 * Created by Tiago on 15/07/2015.
 */
public class Commands {

    public static final String COMMAND_PREFIX = "CMD";
    public static final String COMMAND_SETTIME_PREFIX = COMMAND_PREFIX+" SETTIME S";
    public static final String COMMAND_CLOCKSTYLE_PREFIX = COMMAND_PREFIX+" CLOCKSTYLE";
    public static final String COMMAND_CLOCKCOLOR_PREFIX = COMMAND_PREFIX+" CLOCKCOLOR";
    public static final String COMMAND_CLOCKBRIGHTNESS_PREFIX = COMMAND_PREFIX+" CLOCKBRIGHTNESS";
    public static final String COMMAND_CLOCKLEDTEST_PREFIX = COMMAND_PREFIX+" CLOCKLEDTEST";
    public static final String COMMAND_RADIO_PREFIX = COMMAND_PREFIX+" RADIO";
    public static final String COMMAND_GASSENSOR_PREFIX = COMMAND_PREFIX+" GASSENSOR";

    public static String formatTimeDigits(int num)
    {
        return String.format("%02d", num);
    }

}
