package com.android.emulator.detector;

import android.app.Activity;
import android.content.Context;
import android.os.Bundle;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;

import com.fuzion.emulatordetection.EmulatorDetector;


public class MyActivity extends Activity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_my);
        Button testForEmuButton = (Button) findViewById(R.id.emulatorCheckBtn);

        final Context ctx = getApplicationContext();

        final TextView emulatorLabel = (TextView) findViewById(R.id.emulatorLabel);
        testForEmuButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                if(EmulatorDetector.isEmulator(ctx)){
                    emulatorLabel.setText("This is an emulator");
                }else{
                    emulatorLabel.setText("This is not an emulator");
                }
            }
        });
    }


    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        // Inflate the menu; this adds items to the action bar if it is present.
        getMenuInflater().inflate(R.menu.my, menu);
        return true;
    }

    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        // Handle action bar item clicks here. The action bar will
        // automatically handle clicks on the Home/Up button, so long
        // as you specify a parent activity in AndroidManifest.xml.
        int id = item.getItemId();
        if (id == R.id.action_settings) {
            return true;
        }
        return super.onOptionsItemSelected(item);
    }
}
