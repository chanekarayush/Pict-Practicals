import org.apache.hadoop.conf.Configuration;
import org.apache.hadoop.fs.Path;
import org.apache.hadoop.io.*;
import org.apache.hadoop.mapred.*;
import java.io.IOException;
import java.util.Iterator;

public class WeatherAverage {

    // Mapper Class
    public static class WeatherMapper extends MapReduceBase implements Mapper<LongWritable, Text, Text, Text> {
        private Text location = new Text();
        private Text values = new Text();

        public void map(LongWritable key, Text value, OutputCollector<Text, Text> output, Reporter reporter) throws IOException {
            String line = value.toString();
            String[] fields = line.split(",");

            // Skip header row
            if (key.get() == 0 && line.contains("Location")) return;

            if (fields.length >= 6) {
                location.set(fields[0]); // Location as Key
                values.set(fields[2] + "," + fields[3] + "," + fields[5]); // Temperature, Humidity, Wind Speed
                output.collect(location, values);
            }
        }
    }

    // Reducer Class
    public static class WeatherReducer extends MapReduceBase implements Reducer<Text, Text, Text, Text> {
        public void reduce(Text key, Iterator<Text> values, OutputCollector<Text, Text> output, Reporter reporter) throws IOException {
            double tempSum = 0, humiditySum = 0, windSum = 0;
            int count = 0;

            while (values.hasNext()) {
                String[] fields = values.next().toString().split(",");
                tempSum += Double.parseDouble(fields[0]);
                humiditySum += Double.parseDouble(fields[1]);
                windSum += Double.parseDouble(fields[2]);
                count++;
            }

            // Calculate Averages
            double avgTemp = tempSum / count;
            double avgHumidity = humiditySum / count;
            double avgWindSpeed = windSum / count;
            System.out.println("Location\tAvgTemp\tAvgHumidity\tavgWindSpeed");
            output.collect(key, new Text(String.format("%.2f, %.2f, %.2f", avgTemp, avgHumidity, avgWindSpeed)));
        }
    }

    // Main Method
    public static void main(String[] args) throws Exception {
        JobConf conf = new JobConf(WeatherAverage.class);
        conf.setJobName("Weather Average Calculation");

        conf.setMapperClass(WeatherMapper.class);
        conf.setReducerClass(WeatherReducer.class);

        conf.setOutputKeyClass(Text.class);
        conf.setOutputValueClass(Text.class);

        conf.setInputFormat(TextInputFormat.class);
        conf.setOutputFormat(TextOutputFormat.class);

        FileInputFormat.setInputPaths(conf, new Path(args[0]));
        FileOutputFormat.setOutputPath(conf, new Path(args[1]));

        JobClient.runJob(conf);
    }
}

