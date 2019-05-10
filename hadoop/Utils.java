/**
 * 
 */
/**
 * @author liuqi15
 *
 */
package com.it18zhang.mapreduce.util;

import java.lang.management.ManagementFactory;
import java.lang.management.RuntimeMXBean;
import java.net.InetAddress;
import java.net.Socket;
import java.net.UnknownHostException;

import java.io.OutputStream;

public class Utils {
    
    private static Socket sock;
    private static OutputStream os = null;
    
    static {
        try {
            sock = new Socket("192.168.244.131", 8888);
            os = sock.getOutputStream();
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
    /**
     * 主机名
     **/
    public static String getHost() {
        try {
            return InetAddress.getLocalHost().getHostName();
        } catch (UnknownHostException e) {
            e.printStackTrace();
        }
        return null;
    }
    /**
     * 进程pid
     **/
    public static String getPID() {
        try {
            RuntimeMXBean bean = ManagementFactory.getRuntimeMXBean();
            String name = bean.getName();
            return name.substring(0, name.indexOf("@"));
        } catch (Exception e) {
            e.printStackTrace();
        }
        return null;
    }
    /**
     * 进程tid
     **/
    public static String getTID() {
        try {
            return Thread.currentThread().getName();
        } catch (Exception e) {
            e.printStackTrace();
        }
        return null;
    }
    /**
     * 进程ObjectInfo
     **/
    public static String getOID(Object o) {
        try {
            String className = o.getClass().getSimpleName();
            return className + "@" + o.hashCode();
        } catch (Exception e) {
            e.printStackTrace();
        }
        return null;
    }
    
    public static String prefix(Object o, String info) {
        String str = "[" + getHost() + ":" + getPID() + ":" + getTID() + ":" + getOID(o) +"] " + info;
        return str;
    }
    
    /**
     * 输出
     **/
    public static void outInfo(Object o, String info) {
        try {
            os.write((prefix(o, info) + "\r\n").getBytes());
            os.flush();
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}
