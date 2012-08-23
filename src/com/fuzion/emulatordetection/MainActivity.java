package com.fuzion.emulatordetection;

import android.app.Activity;
import android.os.Bundle;
import android.util.Log;
import android.view.Menu;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Button;

public class MainActivity extends Activity {

	private Button btnClicky;
    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        btnClicky = (Button) this.findViewById(R.id.button1);
        btnClicky.setOnClickListener(new OnClickListener(){
			@Override
			public void onClick(View v) {
				 if(EmulatorDetector.qemuDetection())
					 Log.d("EMUDETECT", "I know you're running on an emulator, so I am not going to do anything malicious");
				 else
					 Log.d("EMUDETECT", "OK, we're on a real device, here's my malicious payload");
			}
        }); 
    }

    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        getMenuInflater().inflate(R.menu.activity_main, menu);
        return true;
    }
}
