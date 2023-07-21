package com.example.localif

import android.content.Intent
import android.graphics.Bitmap
import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.widget.Button
import android.widget.ImageView
import android.widget.Toast
import androidx.activity.result.contract.ActivityResultContracts.TakePicturePreview



class MainActivity : AppCompatActivity() {


    private lateinit var imagePreview: ImageView
    private lateinit var btnCapture: Button
    private lateinit var btnAcceptCapture: Button
    private lateinit var btnDeclineCapture: Button


    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)


        imagePreview = findViewById(R.id.image_preview)
        btnCapture = findViewById(R.id.btn_capture)
        btnAcceptCapture = findViewById(R.id.btn_accept_capture)
        btnDeclineCapture = findViewById(R.id.btn_decline_capture)


        var imageTaken: Bitmap? = null

        val takePicture = registerForActivityResult(TakePicturePreview()) { bitmap: Bitmap? ->
            bitmap?.let {
                imageTaken = it
                imagePreview.setImageBitmap(imageTaken)
            }
        }


        btnCapture.setOnClickListener {
            takePicture.launch(null)
        }


        btnDeclineCapture.setOnClickListener {
            imagePreview.setImageBitmap(null)
            imageTaken = null
        }


        btnAcceptCapture.setOnClickListener {
            if (imageTaken != null){
                val intent = Intent(this, LocalityActivity::class.java)
                intent.putExtra("ImageTaken", imageTaken)
                startActivity(intent)
            } else {
                Toast.makeText(this, "Take a picture before!", Toast.LENGTH_SHORT).show()
            }
        }
    }
}
