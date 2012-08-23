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
					Log.d("EMU","OnClick");
				 EmulatorDetector.qemuDetection();
			}
        }); 
    }

    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        getMenuInflater().inflate(R.menu.activity_main, menu);
        return true;
    }
}
