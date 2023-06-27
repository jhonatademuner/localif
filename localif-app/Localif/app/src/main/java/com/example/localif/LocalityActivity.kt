package com.example.localif


import android.graphics.Bitmap
import android.graphics.Color
import android.os.Bundle
import kotlin.IntArray
import android.widget.Button
import android.widget.ImageView
import android.widget.TextView
import androidx.appcompat.app.AppCompatActivity
import android.util.Log
import java.io.BufferedReader
import java.io.InputStreamReader
import android.widget.Toast


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

        val bitmap = intent?.getParcelableExtra<Bitmap>("ImageTaken")

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
//        Log.d("jDebug - imagesListFirst", imagesList[0].toString())
//        Log.d("jDebug - imagesListFirstLocality", imagesList[0].locality)
//        Log.d("jDebug - imagesListFirstEuclideanDistance", imagesList[0].euclideanDistance.toString())
//        Log.d("jDebug - imagesListFirstSmdDistance", imagesList[0].smdDistance.toString())

        imagesList = sortImagesList(imagesList)

        val topLocalities = topLocalities(imagesList)
        val firstLocality = getMostFrequentLocality(imagesList)

        var localityArr = arrayOf(firstLocality) + topLocalities

        val result = getImageFromName(localityArr)

        localityArr = result.first
        val imageArr = result.second

        localityName.text = localityArr[0]
        localityImage.setImageResource(imageArr[0])


        btnDeclineRoute.setOnClickListener {
            onBackPressed()
        }


        btnAcceptRoute.setOnClickListener {
            Toast.makeText(this, "Coming Soon!", Toast.LENGTH_SHORT).show()
        }


        btnWrongLocality.setOnClickListener {
            Toast.makeText(this, "Coming Soon!", Toast.LENGTH_SHORT).show()
        }

    }


    private fun convertBitmapToPgm(bitmap: Bitmap): Array<IntArray> {
        val originalWidth = bitmap.width
        val originalHeight = bitmap.height
        val targetWidth = 480
        val targetHeight = 800

        val pgmData = Array(targetWidth) { IntArray(targetHeight) { 0 } }

        val pixels = IntArray(originalWidth * originalHeight)
        bitmap.getPixels(pixels, 0, originalWidth, 0, 0, originalWidth, originalHeight)

        val scaleX = originalWidth.toFloat() / targetWidth
        val scaleY = originalHeight.toFloat() / targetHeight

        for (x in 0 until targetWidth) {
            for (y in 0 until targetHeight) {

                val sourceX = (x * scaleX).toInt()
                val sourceY = (y * scaleY).toInt()

                val sourcePixel = pixels[sourceY * originalWidth + sourceX]
                val gray = Color.red(sourcePixel)

                pgmData[x][y] = gray
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
        val distinctLocalities = imagesList.map { it.locality }.distinct()
        return distinctLocalities.take(5).toTypedArray()
    }

    private fun getMostFrequentLocality(nodes: List<Node>): String {
        val localityCount = mutableMapOf<String, Int>()
        var distinctCount = 0
        var mostFrequentLocality: String? = null

        for (node in nodes) {
            val locality = node.locality
            val count = localityCount.getOrDefault(locality, 0)
            localityCount[locality] = count + 1

            if (count == 0) {
                distinctCount++
                if (distinctCount == 5) {
                    mostFrequentLocality = localityCount.maxByOrNull { it.value }?.key
                    break
                }
            }
        }

        if (distinctCount < 5) {
            mostFrequentLocality = localityCount.maxByOrNull { it.value }?.key
        }

        return mostFrequentLocality.toString()
    }

    private fun getImageFromName(localityArr: Array<String>): Pair<Array<String>, IntArray> {
        val arrSize = localityArr.size
        val imageArr = IntArray(arrSize)

        for (i in 0 until arrSize) {
            when (localityArr[i]) {
                "auditory" -> {
                    localityArr[i] = "Auditório"
                    imageArr[i] = R.drawable.auditory
                }

                "block_05" -> {
                    localityArr[i] = "Bloco 05"
                    imageArr[i] = R.drawable.block_05
                }

                "block_08" -> {
                    localityArr[i] = "Bloco 08"
                    imageArr[i] = R.drawable.block_08
                }

                "block_09_bathrooms" -> {
                    localityArr[i] = "Banheiros do Bloco 09"
                    imageArr[i] = R.drawable.block_09_bathrooms
                }

                "college_classrooms" -> {
                    localityArr[i] = "Salas do Ensino Superior"
                    imageArr[i] = R.drawable.college_classrooms
                }

                "staff_rooms" -> {
                    localityArr[i] = "Salas dos Professores"
                    imageArr[i] = R.drawable.staff_rooms
                }

                "technology_classrooms" -> {
                    localityArr[i] = "Laboratórios de Tecnologia"
                    imageArr[i] = R.drawable.technology_classrooms
                }

                "coordination" -> {
                    localityArr[i] = "Cordenação"
                    imageArr[i] = R.drawable.coordination
                }

                "cra" -> {
                    localityArr[i] = "CRA"
                    imageArr[i] = R.drawable.cra
                }

                "ifes_entrance" -> {
                    localityArr[i] = "Entrada do IFES"
                    imageArr[i] = R.drawable.ifes_entrance
                }

                "high_school_garden" -> {
                    localityArr[i] = "Jardim do Ensino Médio"
                    imageArr[i] = R.drawable.high_school_garden
                }

                "laboratories" -> {
                    localityArr[i] = "Laboratórios"
                    imageArr[i] = R.drawable.laboratories
                }

                "leds" -> {
                    localityArr[i] = "LEDS"
                    imageArr[i] = R.drawable.leds
                }

                "library" -> {
                    localityArr[i] = "Biblioteca"
                    imageArr[i] = R.drawable.library
                }

                "main_ramp" -> {
                    localityArr[i] = "Rampa Principal"
                    imageArr[i] = R.drawable.main_ramp
                }

                "parking" -> {
                    localityArr[i] = "Estacionamento"
                    imageArr[i] = R.drawable.parking
                }

                "refectory" -> {
                    localityArr[i] = "Refeitório"
                    imageArr[i] = R.drawable.refectory
                }

                "warehouse" -> {
                    localityArr[i] = "Depósito"
                    imageArr[i] = R.drawable.warehouse
                }

                else -> {
                    localityArr[i] = "Local não encontrado"
                    imageArr[i] = R.drawable.img_placeholder
                }
            }
        }
        return Pair(localityArr, imageArr)
    }

}
