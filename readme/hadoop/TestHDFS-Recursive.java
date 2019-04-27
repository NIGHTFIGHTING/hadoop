package com.it18zhang.myhadoop_maven;

import org.junit.Test;
import org.apache.hadoop.fs.FileStatus;
import org.apache.hadoop.fs.FileSystem;

import org.apache.hadoop.conf.Configuration;
import org.apache.hadoop.fs.Path;

/**
 * 测试hdfs
 **/
public class TestHDFS 
{
	@Test
    public void listFS() throws Exception {
		Configuration conf = new Configuration();
		conf.set("fs.defaultFS", "hdfs://192.168.244.131:8020/");
    	FileSystem fs = FileSystem.get(conf);
    	printlnPath(fs, new Path("/"));
    }
	
	/**
	 * 递归输出hdfs目录结构
	 **/
	private void printlnPath(FileSystem fs, Path p) {
		try {
			// 输出路径
			System.out.println(p.toUri().toString());
			/*if (fs.isFile(p)) {
		        
			} else {
			*/
			if (fs.isDirectory(p)) {
			    FileStatus[] files = fs.listStatus(p);
			    if (files != null && files.length > 0) {
				    for(FileStatus f : files) {
					    Path p0 = f.getPath();
				        printlnPath(fs, p0);
				    }
			    }
			}
		} catch (Exception e) {
			e.printStackTrace();
		}
	}
}

