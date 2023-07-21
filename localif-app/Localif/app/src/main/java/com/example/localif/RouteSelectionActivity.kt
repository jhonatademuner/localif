package com.example.localif

import android.content.Intent
import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.widget.TextView

class RouteSelectionActivity : AppCompatActivity() {
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_route_selection)

        val routeAuditory = findViewById<TextView>(R.id.choose_route_auditory)
        val routeLibrary = findViewById<TextView>(R.id.choose_route_library)
        val routeBlock05 = findViewById<TextView>(R.id.choose_route_block_05)
        val routeBlock08 = findViewById<TextView>(R.id.choose_route_block_08)
        val routeBlock09Bathroom = findViewById<TextView>(R.id.choose_route_block_09_bathrooms)
        val routeCoordination = findViewById<TextView>(R.id.choose_route_coordination)
        val routeCra = findViewById<TextView>(R.id.choose_route_cra)
        val routeWarehouse = findViewById<TextView>(R.id.choose_route_warehouse)
        val routeIfesEntrance = findViewById<TextView>(R.id.choose_route_ifes_entrance)
        val routeParking = findViewById<TextView>(R.id.choose_route_parking)
        val routeHighSchoolGarden = findViewById<TextView>(R.id.choose_route_high_school_garden)
        val routeLaboratories = findViewById<TextView>(R.id.choose_route_laboratories)
        val routeTechnologyClassrooms = findViewById<TextView>(R.id.choose_route_technology_classrooms)
        val routeLeds = findViewById<TextView>(R.id.choose_route_leds)
        val routeMainRamp = findViewById<TextView>(R.id.choose_route_main_ramp)
        val routeRefectory = findViewById<TextView>(R.id.choose_route_refectory)
        val routeCollegeClassrooms = findViewById<TextView>(R.id.choose_route_college_classrooms)
        val routeStaffRooms = findViewById<TextView>(R.id.choose_route_staff_rooms)

        val startLocality = intent.getStringExtra("startLocality")
        var goalLocality: String
        val intent = Intent(this, RouteActivity::class.java)



        routeAuditory.setOnClickListener {
            goalLocality = "auditory"
            intent.putExtra("startLocality", startLocality)
            intent.putExtra("goalLocality", goalLocality)
            startActivity(intent)
        }

        routeLibrary.setOnClickListener {
            goalLocality = "library"
            intent.putExtra("startLocality", startLocality)
            intent.putExtra("goalLocality", goalLocality)
            startActivity(intent)
        }

        routeBlock05.setOnClickListener {
            goalLocality = "block_05"
            intent.putExtra("startLocality", startLocality)
            intent.putExtra("goalLocality", goalLocality)
            startActivity(intent)
        }

        routeBlock08.setOnClickListener {
            goalLocality = "block_08"
            intent.putExtra("startLocality", startLocality)
            intent.putExtra("goalLocality", goalLocality)
            startActivity(intent)
        }

        routeBlock09Bathroom.setOnClickListener {
            goalLocality = "block_09_bathrooms"
            intent.putExtra("startLocality", startLocality)
            intent.putExtra("goalLocality", goalLocality)
            startActivity(intent)
        }

        routeCoordination.setOnClickListener {
            goalLocality = "coordination"
            intent.putExtra("startLocality", startLocality)
            intent.putExtra("goalLocality", goalLocality)
            startActivity(intent)
        }

        routeCra.setOnClickListener {
            goalLocality = "cra"
            intent.putExtra("startLocality", startLocality)
            intent.putExtra("goalLocality", goalLocality)
            startActivity(intent)
        }

        routeWarehouse.setOnClickListener {
            goalLocality = "warehouse"
            intent.putExtra("startLocality", startLocality)
            intent.putExtra("goalLocality", goalLocality)
            startActivity(intent)
        }

        routeIfesEntrance.setOnClickListener {
            goalLocality = "ifes_entrance"
            intent.putExtra("startLocality", startLocality)
            intent.putExtra("goalLocality", goalLocality)
            startActivity(intent)
        }

        routeParking.setOnClickListener {
            goalLocality = "parking"
            intent.putExtra("startLocality", startLocality)
            intent.putExtra("goalLocality", goalLocality)
            startActivity(intent)
        }

        routeHighSchoolGarden.setOnClickListener {
            goalLocality = "high_school_garden"
            intent.putExtra("startLocality", startLocality)
            intent.putExtra("goalLocality", goalLocality)
            startActivity(intent)
        }

        routeLaboratories.setOnClickListener {
            goalLocality = "laboratories"
            intent.putExtra("startLocality", startLocality)
            intent.putExtra("goalLocality", goalLocality)
            startActivity(intent)
        }

        routeTechnologyClassrooms.setOnClickListener {
            goalLocality = "technology_classrooms"
            intent.putExtra("startLocality", startLocality)
            intent.putExtra("goalLocality", goalLocality)
            startActivity(intent)
        }

        routeLeds.setOnClickListener {
            goalLocality = "leds"
            intent.putExtra("startLocality", startLocality)
            intent.putExtra("goalLocality", goalLocality)
            startActivity(intent)
        }

        routeMainRamp.setOnClickListener {
            goalLocality = "main_ramp"
            intent.putExtra("startLocality", startLocality)
            intent.putExtra("goalLocality", goalLocality)
            startActivity(intent)
        }

        routeRefectory.setOnClickListener {
            goalLocality = "refectory"
            intent.putExtra("startLocality", startLocality)
            intent.putExtra("goalLocality", goalLocality)
            startActivity(intent)
        }

        routeCollegeClassrooms.setOnClickListener {
            goalLocality = "college_classrooms"
            intent.putExtra("startLocality", startLocality)
            intent.putExtra("goalLocality", goalLocality)
            startActivity(intent)
        }

        routeStaffRooms.setOnClickListener {
            goalLocality = "staff_rooms"
            intent.putExtra("startLocality", startLocality)
            intent.putExtra("goalLocality", goalLocality)
            startActivity(intent)

        }



    }
}