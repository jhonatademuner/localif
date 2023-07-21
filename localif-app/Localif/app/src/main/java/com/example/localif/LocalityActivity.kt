package com.example.localif


import android.content.Context
import android.content.Intent
import android.graphics.Bitmap
import android.graphics.BitmapFactory
import android.graphics.Color
import android.graphics.drawable.ColorDrawable
import android.os.Bundle
import kotlin.IntArray
import android.widget.Button
import android.widget.ImageView
import android.widget.TextView
import androidx.appcompat.app.AppCompatActivity
import android.util.Log
import android.view.LayoutInflater
import android.view.MotionEvent
import android.view.WindowManager
import java.io.BufferedReader
import java.io.InputStreamReader
import android.widget.Toast
import androidx.appcompat.app.AlertDialog


class ImageRecovery {

    external fun getHistogramVector(matrix: Array<IntArray>): IntArray
    external fun getSmdVector(matrix: Array<IntArray>): DoubleArray
    external fun getEuclideanDistance(vector1: IntArray, vector2: IntArray): Double
    external fun getSmdDistance(vector1: DoubleArray, vector2: DoubleArray): Double


    companion object {
        init {
            System.loadLibrary("localif")
        }
    }
}


class Node(var locality: String, var euclideanDistance: Double, var smdDistance: Double) {
}


class LocalityActivity : AppCompatActivity() {


    private lateinit var localityImage: ImageView
    private lateinit var localityName: TextView
    private lateinit var btnWrongLocality: Button
    private lateinit var btnDeclineRoute: Button
    private lateinit var btnAcceptRoute: Button


    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_locality)

        localityImage = findViewById(R.id.locality_image)
        localityName = findViewById(R.id.locality_name)
        btnWrongLocality = findViewById(R.id.btn_wrong_locality)
        btnDeclineRoute = findViewById(R.id.btn_decline_route)
        btnAcceptRoute = findViewById(R.id.btn_accept_route)


        val imageRecoveryInstance = ImageRecovery()

        var bitmap = intent?.getParcelableExtra<Bitmap>("ImageTaken")
        bitmap = Bitmap.createScaledBitmap(bitmap!!, 480, 800, true)

        val pgmData = convertBitmapToPgm(bitmap!!)

//        Log.d("jDebug - userPgmAddress", pgmData.toString())
//        Log.d("jDebug - userPgmWidth", pgmData.size.toString())
//        Log.d("jDebug - userPgmHeight", pgmData[0].size.toString())

        val userHistogramVector = imageRecoveryInstance.getHistogramVector(pgmData)

//        Log.d("jDebug - userHistogramVectorAddress", userHistogramVector.toString())
//        Log.d("jDebug - userHistogramVectorData", userHistogramVector.joinToString { it.toString() })
//        Log.d("jDebug - userHistogramVectorSum", userHistogramVector.sum().toString())


        val userSmdVector = imageRecoveryInstance.getSmdVector(pgmData)

//        Log.d("jDebug - userSmdVectorAddress", userSmdVector.toString())
//        Log.d("jDebug - userSmdVectorData", userSmdVector.joinToString { it.toString() })
//        Log.d("jDebug - userSmdVectorSum", userSmdVector.sum().toString())


        val entireIndex = getIndex("index.txt") // Strings Vector
        val index = entireIndex.toMutableList()
        index.removeAt(0)


        var imagesList = ArrayList<Node>()
        for (data in index) {
            val indexInfo = data.split(" ")
            val histogramPath = indexInfo[1]
            val smdPath = indexInfo[2]
            val locality = indexInfo[3]

            val histogramVector = readIntVectorFromFile(histogramPath)
            val smdVector = readDoubleVectorFromFile(smdPath)

//            Log.d("jDebug - histogramVector", histogramVector[0].toString())
//            Log.d("jDebug - smdVector", smdVector[0].toString())


            val euclideanDistance = imageRecoveryInstance.getEuclideanDistance(histogramVector, userHistogramVector)
            val smdDistance = imageRecoveryInstance.getSmdDistance(smdVector, userSmdVector)

//            Log.d("jDebug - euclideanDistance", euclideanDistance.toString())
//            Log.d("jDebug - smdDistance", smdDistance.toString())


            imagesList.add(Node(locality, euclideanDistance, smdDistance))
        }

//        Log.d("jDebug - imagesListData", imagesList.toString())

        imagesList = sortImagesList(imagesList)

//        for (i in 0 until imagesList.size){
//            Log.d("jDebug - SortedLocality", imagesList[i].locality)
//            Log.d("jDebug - SortedEuclidean", imagesList[i].euclideanDistance.toString())
//            Log.d("jDebug - SortedSmd", imagesList[i].smdDistance.toString())
//        }


        val topLocalities = topLocalities(imagesList)
        val firstLocality = getMostFrequentLocality(imagesList)

//        Log.d("jDebug - topLocalities", topLocalities.joinToString { it })
//        Log.d("jDebug - firstLocality", firstLocality)

        var localityArr = arrayOf(firstLocality) + topLocalities


        Log.d("jDebug - localityArr", localityArr.joinToString { it })


        val result = getImageFromName(localityArr)
        val localityNameArr = result.first
        val imageArr = result.second
        localityName.text = localityNameArr[0]
        localityImage.setImageResource(imageArr[0])

        Log.d("jDebug - localityNameArr", localityNameArr.joinToString { it })
//        Log.d("jDebug - imageArr", imageArr.joinToString { it.toString() })



        btnDeclineRoute.setOnClickListener {
            onBackPressed()
        }


        btnAcceptRoute.setOnClickListener {
            val intent = Intent(this, RouteSelectionActivity::class.java)
            intent.putExtra("startLocality", localityArr[0])
            startActivity(intent)
        }

        btnWrongLocality.setOnClickListener{
            localityArr = showPopup(this, localityArr, localityNameArr)
        }

    }

    private fun changeImage(localityArr: Array<String>){
        val result = getImageFromName(localityArr)
        val localityNameArr = result.first
        val imageArr = result.second
        localityName.text = localityNameArr[0]
        localityImage.setImageResource(imageArr[0])
    }

    private fun showPopup(context: Context, localityArr: Array<String>, localityNameArr: Array<String>): Array<String> {
        val builder = AlertDialog.Builder(context)
        val inflater = LayoutInflater.from(context)
        val popupView = inflater.inflate(R.layout.popup_layout, null)
        builder.setView(popupView)

        val popupText1 = popupView.findViewById<TextView>(R.id.wrong_locality_text_popup_1)
        val popupText2 = popupView.findViewById<TextView>(R.id.wrong_locality_text_popup_2)
        val popupText3 = popupView.findViewById<TextView>(R.id.wrong_locality_text_popup_3)
        val popupText4 = popupView.findViewById<TextView>(R.id.wrong_locality_text_popup_4)
        val popupText5 = popupView.findViewById<TextView>(R.id.wrong_locality_text_popup_5)

        popupText1.text = localityNameArr[1]
        popupText2.text = localityNameArr[2]
        popupText3.text = localityNameArr[3]
        popupText4.text = localityNameArr[4]
        popupText5.text = localityNameArr[5]

        val dialog = builder.create()
        dialog.show()

        dialog.window?.setBackgroundDrawable(ColorDrawable(Color.TRANSPARENT))
        dialog.window?.setLayout(
            WindowManager.LayoutParams.MATCH_PARENT,
            WindowManager.LayoutParams.MATCH_PARENT
        )

        popupText1.setOnClickListener{
            localityArr[0] = localityArr[1]
            changeImage(localityArr)
            dialog.dismiss()
        }

        popupText2.setOnClickListener{
            localityArr[0] = localityArr[2]
            changeImage(localityArr)
            dialog.dismiss()
        }

        popupText3.setOnClickListener{
            localityArr[0] = localityArr[3]
            changeImage(localityArr)
            dialog.dismiss()
        }

        popupText4.setOnClickListener{
            localityArr[0] = localityArr[4]
            changeImage(localityArr)
            dialog.dismiss()
        }

        popupText5.setOnClickListener{
            localityArr[0] = localityArr[5]
            changeImage(localityArr)
            dialog.dismiss()
        }

        popupView.setOnClickListener {
            dialog.dismiss()
        }

        return localityArr
    }


    private fun convertBitmapToPgm(bitmap: Bitmap): Array<IntArray> {
        val width = bitmap.width
        val height = bitmap.height

        val grayscaleData = IntArray(width * height)
        bitmap.getPixels(grayscaleData, 0, width, 0, 0, width, height)

        val pgmData = Array(height) { IntArray(width) }

        for (y in 0 until height) {
            for (x in 0 until width) {
                val pixel = grayscaleData[y * width + x]
                val gray = Color.red(pixel)
                pgmData[y][x] = gray
            }
        }

        return pgmData
    }

    private fun getIndex(filename: String): List<String> {
        val assetManager = applicationContext.assets
        val lines = mutableListOf<String>()
        val inputStream = assetManager.open(filename)
        val reader = BufferedReader(InputStreamReader(inputStream))
        reader.useLines { lines.addAll(it) }
        return lines
    }

    private fun readIntVectorFromFile(filePath: String): IntArray {
        val fileContent = getIndex(filePath)
        val stringArray = fileContent[0].trim().split(" ")
        return stringArray.map { it.toInt() }.toIntArray()
    }

    private fun readDoubleVectorFromFile(filePath: String): DoubleArray {
        val fileContent = getIndex(filePath)
        val stringArray = fileContent[0].trim().split(" ")
        return stringArray.map { it.toDouble() }.toDoubleArray()
    }

    private fun compareNodes(node1: Node, node2: Node): Boolean {
        var w1 = 0
        var w2 = 0
        val euclideanWeight = 6
        val smdWeight = 3

        if (node1.euclideanDistance < node2.euclideanDistance) {
            w2 += euclideanWeight
        } else if (node1.euclideanDistance > node2.euclideanDistance) {
            w1 += euclideanWeight
        }
        if (node1.smdDistance < node2.smdDistance) {
            w2 += smdWeight
        } else if (node1.smdDistance > node2.smdDistance) {
            w1 += smdWeight
        }
        return w1 > w2
    }

    private fun sortImagesList(imagesList: ArrayList<Node>): ArrayList<Node> {
        val n = imagesList.size
        var swapped: Boolean
        do {
            swapped = false
            for (i in 0 until n - 1) {
                if (compareNodes(imagesList[i], imagesList[i + 1])) {
                    val temp = imagesList[i]
                    imagesList[i] = imagesList[i + 1]
                    imagesList[i + 1] = temp
                    swapped = true
                }
            }
        } while (swapped)
        return imagesList
    }


    private fun topLocalities(imagesList: ArrayList<Node>): Array<String> {

        var differentLocalities = 0
        val topLocalities = arrayOf("","","","","")
        for (i in 0 until imagesList.size){
            if (!(imagesList[i].locality in topLocalities)){
                topLocalities[differentLocalities] = imagesList[i].locality
                differentLocalities += 1
                if (differentLocalities >= 5){
                    break
                }
            }
        }
        return topLocalities
    }

    private fun getMostFrequentLocality(imagesList: ArrayList<Node>): String {

        val localityCount = arrayOf(0, 0, 0, 0, 0)
        val localities: Array<String> = arrayOf("", "", "", "", "")
        for (i in 0 until 5){
            localities[i] = imagesList[i].locality
            localityCount[i] += 1
        }
        for (i in 0 until 5){
            for (j in i + 1 until 5){
                if(localities[i] == localities[j]){
                    localityCount[i] += 1
                }
            }
        }
        var max = 0
        var maxIndex = 0
        for (i in 0 until 5){
            if (localityCount[i] > max){
                max = localityCount[i]
                maxIndex = i
            }
        }
        return localities[maxIndex]
    }


    private fun getImageFromName(localityArr: Array<String>): Pair<Array<String>, IntArray> {
        val arrSize = localityArr.size
        val modifiedLocalityArr = Array(arrSize) { "" }
        val imageArr = IntArray(arrSize)

        for (i in 0 until arrSize) {
            when (localityArr[i]) {
                "auditory" -> {
                    modifiedLocalityArr[i] = "Auditório"
                    imageArr[i] = R.drawable.auditory
                }

                "block_05" -> {
                    modifiedLocalityArr[i] = "Bloco 05"
                    imageArr[i] = R.drawable.block_05
                }

                "block_08" -> {
                    modifiedLocalityArr[i] = "Bloco 08"
                    imageArr[i] = R.drawable.block_08
                }

                "block_09_bathrooms" -> {
                    modifiedLocalityArr[i] = "Banheiros do Bloco 09"
                    imageArr[i] = R.drawable.block_09_bathrooms
                }

                "college_classrooms" -> {
                    modifiedLocalityArr[i] = "Salas do Ensino Superior"
                    imageArr[i] = R.drawable.college_classrooms
                }

                "staff_rooms" -> {
                    modifiedLocalityArr[i] = "Salas dos Professores"
                    imageArr[i] = R.drawable.staff_rooms
                }

                "technology_classrooms" -> {
                    modifiedLocalityArr[i] = "Laboratórios de Tecnologia"
                    imageArr[i] = R.drawable.technology_classrooms
                }

                "coordination" -> {
                    modifiedLocalityArr[i] = "Cordenação"
                    imageArr[i] = R.drawable.coordination
                }

                "cra" -> {
                    modifiedLocalityArr[i] = "CRA"
                    imageArr[i] = R.drawable.cra
                }

                "ifes_entrance" -> {
                    modifiedLocalityArr[i] = "Entrada do IFES"
                    imageArr[i] = R.drawable.ifes_entrance
                }

                "high_school_garden" -> {
                    modifiedLocalityArr[i] = "Jardim do Ensino Médio"
                    imageArr[i] = R.drawable.high_school_garden
                }

                "laboratories" -> {
                    modifiedLocalityArr[i] = "Laboratórios"
                    imageArr[i] = R.drawable.laboratories
                }

                "leds" -> {
                    modifiedLocalityArr[i] = "LEDS"
                    imageArr[i] = R.drawable.leds
                }

                "library" -> {
                    modifiedLocalityArr[i] = "Biblioteca"
                    imageArr[i] = R.drawable.library
                }

                "main_ramp" -> {
                    modifiedLocalityArr[i] = "Rampa Principal"
                    imageArr[i] = R.drawable.main_ramp
                }

                "parking" -> {
                    modifiedLocalityArr[i] = "Estacionamento"
                    imageArr[i] = R.drawable.parking
                }

                "refectory" -> {
                    modifiedLocalityArr[i] = "Refeitório"
                    imageArr[i] = R.drawable.refectory
                }

                "warehouse" -> {
                    modifiedLocalityArr[i] = "Depósito"
                    imageArr[i] = R.drawable.warehouse
                }

                else -> {
                    modifiedLocalityArr[i] = "Local não encontrado"
                    imageArr[i] = R.drawable.img_placeholder
                }
            }
        }

        return Pair(modifiedLocalityArr, imageArr)
    }

}
