// Declare the package name for your app
package com.example.localif

// Import the classes you need from the Android framework and the Activity Result APIs
import android.content.Intent
import android.graphics.Bitmap
import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.widget.Button
import android.widget.ImageView
import androidx.activity.result.contract.ActivityResultContracts.TakePicturePreview

// Define your main activity class that inherits from AppCompatActivity
class HomeActivity : AppCompatActivity() {

    // Declare the views and buttons as lateinit variables that will be initialized later
    private lateinit var imagePreview: ImageView
    private lateinit var btnCapture : Button
    private lateinit var btnAcceptCapture : Button
    private lateinit var btnDeclineCapture : Button


    // Override the onCreate method that is called when the activity is created
    override fun onCreate(savedInstanceState: Bundle?) {
        // Call the super method to perform the default initialization of the activity
        super.onCreate(savedInstanceState)
        // Set the layout resource file for this activity
        setContentView(R.layout.activity_home)

        // Find the views and buttons by their IDs and assign them to the variables
        imagePreview = findViewById(R.id.image_preview)
        btnCapture = findViewById(R.id.btn_capture)
        btnAcceptCapture = findViewById(R.id.btn_accept_capture)
        btnDeclineCapture = findViewById(R.id.btn_decline_capture)

        // Register a callback and get a launcher for the TakePicturePreview contract, which allows you to capture an image and get a bitmap as a result
        val takePicture = registerForActivityResult(TakePicturePreview()) { bitmap: Bitmap? ->
            // Use a safe call operator to handle the null case of the bitmap parameter
            bitmap?.let {
                // Set the bitmap as the source of the image preview view
                imagePreview.setImageBitmap(it)
            }
        }

        // Set an onClick listener for the capture button
        btnCapture.setOnClickListener {
            // Launch the camera activity for result using the launcher and pass null as the input since it is not used by this contract
            takePicture.launch(null)
        }

        // Set an onClick listener for the decline button (this part is not implemented yet)
        btnDeclineCapture.setOnClickListener{
            if(imagePreview != null) {
                imagePreview.setImageBitmap(null)
            }
        }

        btnAcceptCapture.setOnClickListener{
            // ||===================================||
            // ||IMAGE RECOVERY ALGORITHM ENTER HERE||
            // ||===================================||

            // Intents are objects of the android.content.Intent type. Your code can send them to the Android system defining
            // the components you are targeting. Intent to start an activity called SecondActivity with the following code.
            val intent = Intent(this, LocalityActivity::class.java)
            // start the activity connect to the specified class
            startActivity(intent)
        }
    }
}