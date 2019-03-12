package com.it18zhang.hadoop273.hdfs;

import java.io.InputStream;
import java.net.MalformedURLException;
import java.net.URL;
import java.net.URLConnection;

import org.apache.commons.compress.utils.IOUtils;
import org.apache.commons.configuration.Configuration;
import org.apache.commons.io.output.ByteArrayOutputStream;
import org.apache.hadoop.fs.FSDataInputStream;
import org.apache.hadoop.fs.FSDataOutputStream;
import org.apache.hadoop.fs.FileSystem;
import org.apache.hadoop.fs.FsUrlStreamHandlerFactory;
import org.junit.Test;



public class TestHDFS {
    @Test
    public void readFile() throws Exception {
        URL.setURLStreamHandlerFactory(new FsUrlStreamHandlerFactory());
        URL url = new URL("hdfs://192.168.244.131:8020/user/centos/hadoop/index.html");
        URLConnection conn = url.openConnection();
        InputStream is= conn.getInputStream();
        byte[] buf = new byte[is.available()];
        is.read(buf);
        is.close();
        String str = new String(buf);
        System.out.println(str);
     }
    
    @Test
    public void readFileByAPI() throws Exception {
        Configuration conf = new Configuration();
        conf = set("fs.defaultFS", "hdfs://192.168.244.131:8020/");
        FileSystem fs = FileSystem.get(conf);
        Path p = new Path("/user/centos/hadoop/index.html");
        byte[] buf = new byte[1024];
        int len = -1;
        
        ByteArrayOutputStream baos = new ByteArrayOutputStream();
        while((len = fis.read(buf)) != -1){
            baos.write(buf, 0, len);
        }
        fis.close();
        baos.close();
        System.out.println(new String(baos.toByteArray()));
    }
    
    @Test
    public void readFileByAPI2() throws Exception {
        Configuration conf = new Configuration();
        conf = set("fs.defaultFS", "hdfs://192.168.244.131:8020/");
        FileSystem fs = FileSystem.get(conf);
        ByteArrayOutputStream baos = new ByteArrayOutputStream();
        Path p = new Path("/user/centos/hadoop/index.html");
        FSDataInputStream fis = fs.open(p);
        IOUtils.copyBytes(fis, baos);
        System.out.println(new String(baos.toByteArray()));
    }
    
    @Test
    public void mkdir() throws Exception {
        Configuration conf = new Configuration();
        conf = set("fs.defaultFS", "hdfs://192.168.244.131:8020/");
        FileSystem fs = FileSystem.get(conf);
        fs.mkdirs(new Path("/user/centos/myhadoop"))
    }
    @Test
    public void putFile() throws Exception {
        Configuration conf = new Configuration();
        conf = set("fs.defaultFS", "hdfs://192.168.244.131:8020/");
        FileSystem fs = FileSystem.get(conf);
        FSDataOutputStream out = fs.create(new Path("/user/centos/myhadoop/a.txt"));
        out.write("helloworld", getBytes());
        out.close();
    }
    @Test
    public void removeFile() throws Exception {
        Configuration conf = new Configuration();
        conf = set("fs.defaultFS", "hdfs://192.168.244.131:8020/");
        FileSystem fs = FileSystem.get(conf);
        Path p = new Path("/user/centos/myhadoop");
        fs.delete(p, true);
    }
}
