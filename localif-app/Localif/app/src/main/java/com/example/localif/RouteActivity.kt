package com.example.localif

import android.content.Context
import android.graphics.Color
import android.graphics.drawable.ColorDrawable
import androidx.core.view.ViewCompat
import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.util.Log
import android.view.LayoutInflater
import android.view.WindowManager
import android.widget.ImageView
import android.widget.TextView
import androidx.appcompat.app.AlertDialog
import java.util.*


class RouteActivity : AppCompatActivity() {

    private lateinit var graphNode1: ImageView
    private lateinit var graphNode2: ImageView
    private lateinit var graphNode3: ImageView
    private lateinit var graphNode4: ImageView
    private lateinit var graphNode5: ImageView
    private lateinit var graphNode6: ImageView
    private lateinit var graphNode7: ImageView
    private lateinit var graphNode8: ImageView
    private lateinit var graphNode9: ImageView
    private lateinit var graphNode10: ImageView
    private lateinit var graphNode11: ImageView
    private lateinit var graphNode12: ImageView
    private lateinit var graphNode13: ImageView
    private lateinit var graphNode14: ImageView
    private lateinit var graphNode15: ImageView
    private lateinit var graphNode16: ImageView
    private lateinit var graphNode17: ImageView
    private lateinit var graphNode18: ImageView

    private lateinit var graphPath1: ImageView
    private lateinit var graphPath2: ImageView
    private lateinit var graphPath3: ImageView
    private lateinit var graphPath4: ImageView
    private lateinit var graphPath5: ImageView
    private lateinit var graphPath6: ImageView
    private lateinit var graphPath7: ImageView
    private lateinit var graphPath8: ImageView
    private lateinit var graphPath9: ImageView
    private lateinit var graphPath10: ImageView
    private lateinit var graphPath11: ImageView
    private lateinit var graphPath12: ImageView
    private lateinit var graphPath13: ImageView
    private lateinit var graphPath14: ImageView
    private lateinit var graphPath15: ImageView
    private lateinit var graphPath16: ImageView
    private lateinit var graphPath17: ImageView
    private lateinit var graphPath18: ImageView
    private lateinit var graphPath19: ImageView
    private lateinit var graphPath20: ImageView
    private lateinit var graphPath21: ImageView
    private lateinit var graphPath22: ImageView
    private lateinit var graphPath23: ImageView
    private lateinit var graphPath24: ImageView
    private lateinit var graphPath25: ImageView
    private lateinit var graphPath26: ImageView
    private lateinit var graphPath27: ImageView
    private lateinit var graphPath28: ImageView
    private lateinit var graphPath29: ImageView

    private var goalLocality: String = ""

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_route)

        graphNode1 = findViewById(R.id.node_01)
        graphNode2 = findViewById(R.id.node_02)
        graphNode3 = findViewById(R.id.node_03)
        graphNode4 = findViewById(R.id.node_04)
        graphNode5 = findViewById(R.id.node_05)
        graphNode6 = findViewById(R.id.node_06)
        graphNode7 = findViewById(R.id.node_07)
        graphNode8 = findViewById(R.id.node_08)
        graphNode9 = findViewById(R.id.node_09)
        graphNode10 = findViewById(R.id.node_10)
        graphNode11 = findViewById(R.id.node_11)
        graphNode12 = findViewById(R.id.node_12)
        graphNode13 = findViewById(R.id.node_13)
        graphNode14 = findViewById(R.id.node_14)
        graphNode15 = findViewById(R.id.node_15)
        graphNode16 = findViewById(R.id.node_16)
        graphNode17 = findViewById(R.id.node_17)
        graphNode18 = findViewById(R.id.node_18)


        graphPath1 = findViewById(R.id.path_01)
        graphPath2 = findViewById(R.id.path_02)
        graphPath3 = findViewById(R.id.path_03)
        graphPath4 = findViewById(R.id.path_04)
        graphPath5 = findViewById(R.id.path_05)
        graphPath6 = findViewById(R.id.path_06)
        graphPath7 = findViewById(R.id.path_07)
        graphPath8 = findViewById(R.id.path_08)
        graphPath9 = findViewById(R.id.path_09)
        graphPath10 = findViewById(R.id.path_10)
        graphPath11 = findViewById(R.id.path_11)
        graphPath12 = findViewById(R.id.path_12)
        graphPath13 = findViewById(R.id.path_13)
        graphPath14 = findViewById(R.id.path_14)
        graphPath15 = findViewById(R.id.path_15)
        graphPath16 = findViewById(R.id.path_16)
        graphPath17 = findViewById(R.id.path_17)
        graphPath18 = findViewById(R.id.path_18)
        graphPath19 = findViewById(R.id.path_19)
        graphPath20 = findViewById(R.id.path_20)
        graphPath21 = findViewById(R.id.path_21)
        graphPath22 = findViewById(R.id.path_22)
        graphPath23 = findViewById(R.id.path_23)
        graphPath24 = findViewById(R.id.path_24)
        graphPath25 = findViewById(R.id.path_25)
        graphPath26 = findViewById(R.id.path_26)
        graphPath27 = findViewById(R.id.path_27)
        graphPath28 = findViewById(R.id.path_28)
        graphPath29 = findViewById(R.id.path_29)


        val startLocality = intent.getStringExtra("startLocality")
        val goalLocality = intent.getStringExtra("goalLocality")

        val adjacencyList = mapOf(
            1 to listOf(2 to 4.0),
            2 to listOf(3 to 3.0, 1 to 4.0),
            3 to listOf(4 to 4.0, 6 to 3.0, 11 to 4.0, 9 to 3.0, 15 to 4.0, 2 to 3.0),
            4 to listOf(3 to 4.0, 6 to 4.0, 11 to 6.0, 9 to 4.0, 10 to 4.0, 15 to 4.0),
            5 to listOf(9 to 2.0, 13 to 2.0, 12 to 3.0, 7 to 3.0, 10 to 4.0),
            6 to listOf(11 to 1.0, 15 to 2.0, 9 to 2.0, 4 to 4.0, 3 to 3.0),
            7 to listOf(10 to 2.0, 12 to 1.0, 5 to 3.0, 9 to 3.0, 13 to 3.0),
            8 to listOf(14 to 1.0),
            9 to listOf(5 to 2.0, 13 to 1.0, 15 to 2.0, 7 to 3.0, 10 to 2.0, 12 to 3.0, 11 to 1.0, 6 to 2.0, 3 to 3.0, 4 to 4.0),
            10 to listOf(4 to 2.0, 16 to 2.0, 12 to 1.0, 7 to 1.0, 5 to 3.0, 9 to 2.0, 13 to 3.0),
            11 to listOf(9 to 1.0, 15 to 2.0, 6 to 1.0, 17 to 3.0, 3 to 3.0, 4 to 6.0),
            12 to listOf(10 to 1.0, 7 to 1.0, 5 to 3.0, 9 to 2.0, 13 to 2.0),
            13 to listOf(9 to 1.0, 5 to 2.0, 12 to 3.0, 7 to 3.0, 10 to 4.0),
            14 to listOf(8 to 1.0, 17 to 2.0),
            15 to listOf(11 to 1.0, 6 to 2.0, 3 to 3.0, 4 to 4.0, 18 to 2.0, 9 to 1.0),
            16 to listOf(10 to 1.0),
            17 to listOf(11 to 2.0, 14 to 1.0),
            18 to listOf(15 to 1.0)
        )


        Log.d("jDebug - startLocality", startLocality.toString())
        Log.d("jDebug - goalLocality", goalLocality.toString())

        val graph = Graph(adjacencyList)

        val localityNodes = arrayOf("warehouse",                "refectory",            "staff_rooms",
                                    "technology_classrooms",    "auditory",             "high_school_garden",
                                    "coordination",             "leds",                 "main_ramp",
                                    "college_classrooms",       "ifes_entrance",        "block_09_bathrooms",
                                    "library",                  "block_08",             "cra",
                                    "laboratories",             "parking",              "block_05")


        val startNode = localityNodes.indexOf(startLocality) + 1
        val goalNode = localityNodes.indexOf(goalLocality) + 1

        Log.d("jDebug - startNode", startNode.toString())
        Log.d("jDebug - goalNode", goalNode.toString())

        val bestPath = graph.astar(startNode, goalNode)

        Log.d("jDebug - bestPath", bestPath.toString())

        showBestPath(bestPath)
//        Log.d("jDebug", bestPath.joinToString { it.toString() })
    }

    private fun showBestPath(pathArray: List<Int>){

        showBestPathNodes(pathArray)

        for (i in 0 until pathArray.size - 1) {
            if (pathArray[i] == 1 && pathArray[i + 1] == 2){
                activePaths(listOf(1, 2))
            }

            else if (pathArray[i] == 2){
                if (pathArray[i + 1] == 3){
                    activePaths(listOf(3))
                } else if (pathArray[i + 1] == 1){
                    activePaths(listOf(1, 2))
                }
            }

            else if (pathArray[i] == 3) {
                if (pathArray[i + 1] == 4) {
                    activePaths(listOf(4, 5))
                } else if (pathArray[i + 1] == 6) {
                    activePaths(listOf(4, 6, 7))
                } else if (pathArray[i + 1] == 11) {
                    activePaths(listOf(4, 6, 8, 9))
                } else if (pathArray[i + 1] == 9) {
                    activePaths(listOf(4, 6, 8, 10, 15))
                } else if (pathArray[i + 1] == 15) {
                    activePaths(listOf(4, 6, 8, 15, 16))
                }else if (pathArray[i + 1] == 2) {
                    activePaths(listOf(3))
                }
            }

            else if (pathArray[i] == 4) {
                if (pathArray[i + 1] == 3) {
                    activePaths(listOf(4, 5))
                } else if (pathArray[i + 1] == 6) {
                    activePaths(listOf(5, 6, 7))
                } else if (pathArray[i + 1] == 11) {
                    activePaths(listOf(5, 6, 8, 9))
                } else if (pathArray[i + 1] == 9) {
                    activePaths(listOf(5, 6, 8, 10, 15))
                } else if (pathArray[i + 1] == 10) {
                    activePaths(listOf(23))
                } else if (pathArray[i + 1] == 15) {
                    activePaths(listOf(5, 6, 8, 15, 16))
                }
            }

            else if (pathArray[i] == 5) {
                if (pathArray[i + 1] == 9) {
                    activePaths(listOf(11, 12))
                } else if (pathArray[i + 1] == 13) {
                    activePaths(listOf(12, 13, 14))
                } else if (pathArray[i + 1] == 12) {
                    activePaths(listOf(12, 19, 21))
                } else if (pathArray[i + 1] == 7) {
                    activePaths(listOf(12, 19, 20))
                } else if (pathArray[i + 1] == 10) {
                    activePaths(listOf(12, 19, 22))
                }
            }

            else if (pathArray[i] == 6) {
                if (pathArray[i + 1] == 11) {
                    activePaths(listOf(7, 8, 9))
                } else if (pathArray[i + 1] == 15) {
                    activePaths(listOf(7, 8, 15, 16))
                }  else if (pathArray[i + 1] == 9) {
                    activePaths(listOf(7, 8, 15, 10))
                }  else if (pathArray[i + 1] == 4) {
                    activePaths(listOf(7, 6, 5))
                }  else if (pathArray[i + 1] == 3) {
                    activePaths(listOf(7, 6, 4))
                }
            }

            else if (pathArray[i] == 7) {
                if (pathArray[i + 1] == 10) {
                    activePaths(listOf(20, 22))
                } else if (pathArray[i + 1] == 12) {
                    activePaths(listOf(20, 21))
                }  else if (pathArray[i + 1] == 5) {
                    activePaths(listOf(20, 19, 12))
                }  else if (pathArray[i + 1] == 9) {
                    activePaths(listOf(20, 19, 11))
                }  else if (pathArray[i + 1] == 13) {
                    activePaths(listOf(20, 19, 13, 14))
                }
            }

            else if (pathArray[i] == 8) {
                if (pathArray[i + 1] == 14) {
                    activePaths(listOf(29))
                }
            }

            else if (pathArray[i] == 9) {
                if (pathArray[i + 1] == 5) {
                    activePaths(listOf(11, 12))
                } else if (pathArray[i + 1] == 13) {
                    activePaths(listOf(11, 13, 14))
                }  else if (pathArray[i + 1] == 15) {
                    activePaths(listOf(10, 16))
                }  else if (pathArray[i + 1] == 7) {
                    activePaths(listOf(11, 19, 20))
                }  else if (pathArray[i + 1] == 10) {
                    activePaths(listOf(11, 19, 22))
                }  else if (pathArray[i + 1] == 12) {
                    activePaths(listOf(11, 19, 21))
                }  else if (pathArray[i + 1] == 11) {
                    activePaths(listOf(9, 10, 15))
                }  else if (pathArray[i + 1] == 6) {
                    activePaths(listOf(7, 8, 10, 15))
                }  else if (pathArray[i + 1] == 3) {
                    activePaths(listOf(6, 4, 8, 10, 15))
                }  else if (pathArray[i + 1] == 4) {
                    activePaths(listOf(6, 5, 8, 10, 15))
                }
            }

            else if (pathArray[i] == 10) {
                if (pathArray[i + 1] == 4) {
                    activePaths(listOf(23))
                } else if (pathArray[i + 1] == 16) {
                    activePaths(listOf(24))
                } else if (pathArray[i + 1] == 12) {
                    activePaths(listOf(21, 22))
                } else if (pathArray[i + 1] == 7) {
                    activePaths(listOf(20, 22))
                } else if (pathArray[i + 1] == 5) {
                    activePaths(listOf(19, 22, 12))
                } else if (pathArray[i + 1] == 9) {
                    activePaths(listOf(19, 22, 11))
                } else if (pathArray[i + 1] == 13) {
                    activePaths(listOf(19, 22, 13, 14))
                }
            }

            else if (pathArray[i] == 11) {
                if (pathArray[i + 1] == 9) {
                    activePaths(listOf(9, 10, 15))
                } else if (pathArray[i + 1] == 15) {
                    activePaths(listOf(9, 15, 16))
                } else if (pathArray[i + 1] == 6) {
                    activePaths(listOf(9, 8, 7))
                } else if (pathArray[i + 1] == 17) {
                    activePaths(listOf(25, 26))
                } else if (pathArray[i + 1] == 3) {
                    activePaths(listOf(9, 8, 6, 4))
                } else if (pathArray[i + 1] == 4) {
                    activePaths(listOf(9, 8, 6, 5))
                }
            }

            else if (pathArray[i] == 12) {
                if (pathArray[i + 1] == 10) {
                    activePaths(listOf(21, 22))
                } else if (pathArray[i + 1] == 7) {
                    activePaths(listOf(21, 20))
                } else if (pathArray[i + 1] == 5) {
                    activePaths(listOf(21, 19, 12))
                } else if (pathArray[i + 1] == 9) {
                    activePaths(listOf(21, 19, 11))
                } else if (pathArray[i + 1] == 13) {
                    activePaths(listOf(21, 19, 13, 14))
                }
            }

            else if (pathArray[i] == 13) {
                if (pathArray[i + 1] == 9) {
                    activePaths(listOf(11, 13, 14))
                } else if (pathArray[i + 1] == 5) {
                    activePaths(listOf(12, 13, 14))
                } else if (pathArray[i + 1] == 12) {
                    activePaths(listOf(14, 13, 19, 21))
                } else if (pathArray[i + 1] == 7) {
                    activePaths(listOf(14, 13, 19, 20))
                } else if (pathArray[i + 1] == 10) {
                    activePaths(listOf(14, 13, 19, 22))
                }
            }

            else if (pathArray[i] == 14) {
                if (pathArray[i + 1] == 8) {
                    activePaths(listOf(29))
                } else if (pathArray[i + 1] == 17) {
                    activePaths(listOf(27,28))
                }
            }

            else if (pathArray[i] == 15) {
                if (pathArray[i + 1] == 11) {
                    activePaths(listOf(16, 15, 9))
                } else if (pathArray[i + 1] == 6) {
                    activePaths(listOf(16, 15, 8, 7))
                } else if (pathArray[i + 1] == 3) {
                    activePaths(listOf(16, 15, 8, 6, 4))
                } else if (pathArray[i + 1] == 4) {
                    activePaths(listOf(16, 15, 8, 6, 5))
                } else if (pathArray[i + 1] == 18) {
                    activePaths(listOf(17, 18))
                } else if (pathArray[i + 1] == 9) {
                    activePaths(listOf(16, 10))
                }
            }

            else if (pathArray[i] == 16) {
                if (pathArray[i + 1] == 10) {
                    activePaths(listOf(24))
                }
            }

            else if (pathArray[i] == 17) {
                if (pathArray[i + 1] == 11) {
                    activePaths(listOf(25, 26))
                } else if (pathArray[i + 1] == 14) {
                    activePaths(listOf(27, 28))
                }
            }

            else if (pathArray[i] == 18) {
                if (pathArray[i + 1] == 15) {
                    activePaths(listOf(17, 18))
                }
            }
        }
    }

    private fun showBestPathNodes(pathArray: List<Int>){
        val graphNodes = arrayOf(
            graphNode1, graphNode2, graphNode3, graphNode4, graphNode5, graphNode6,
            graphNode7, graphNode8, graphNode9, graphNode10, graphNode11, graphNode12,
            graphNode13, graphNode14, graphNode15, graphNode16, graphNode17, graphNode18
        )

        for (i in graphNodes.indices) {
            if (pathArray.contains(i + 1)) {
                graphNodes[i].setImageResource(R.drawable.graph_node_active)
                ViewCompat.setElevation(graphNodes[i], 30f)
            } else {
                graphNodes[i].setImageResource(R.drawable.graph_node)
            }
        }

        graphNodes[pathArray[0] - 1].setImageResource(R.drawable.graph_node_start)

    }



    private fun activePaths(pathArray: List<Int>){
        val graphPaths = arrayOf(
            graphPath1, graphPath2, graphPath3, graphPath4, graphPath5, graphPath6,
            graphPath7, graphPath8, graphPath9, graphPath10, graphPath11, graphPath12,
            graphPath13, graphPath14, graphPath15, graphPath16, graphPath17, graphPath18,
            graphPath19, graphPath20, graphPath21, graphPath22, graphPath23, graphPath24,
            graphPath25, graphPath26, graphPath27, graphPath28, graphPath29
        )

        for (i in pathArray){
            graphPaths[i - 1].setImageResource(R.drawable.graph_path_active)
            ViewCompat.setElevation(graphPaths[i - 1], 20f)
        }
    }

}

data class GraphNode(val id: Int, val heuristic: Double) : Comparable<GraphNode> {
    var gScore = Double.MAX_VALUE
    var fScore = Double.MAX_VALUE
    var parent: GraphNode? = null

    override fun compareTo(other: GraphNode): Int {
        return fScore.compareTo(other.fScore)
    }
}

class Graph(val adjacencyList: Map<Int, List<Pair<Int, Double>>>) {
    fun astar(startId: Int, goalId: Int): List<Int> {
        val openSet = PriorityQueue<GraphNode>()
        val closedSet = mutableSetOf<GraphNode>()

        val startNode = GraphNode(startId, 0.0)
        startNode.gScore = 0.0
        startNode.fScore = startNode.heuristic

        openSet.add(startNode)

        while (openSet.isNotEmpty()) {
            val current = openSet.poll()
            if (current.id == goalId) {
                return reconstructPath(current)
            }

            closedSet.add(current)

            val neighbors = adjacencyList[current.id] ?: emptyList()
            for ((neighborId, edgeCost) in neighbors) {
                val neighbor = GraphNode(neighborId, 0.0)
                val tentativeGScore = current.gScore + edgeCost

                if (closedSet.contains(neighbor) && tentativeGScore >= neighbor.gScore) {
                    continue
                }

                if (!openSet.contains(neighbor) || tentativeGScore < neighbor.gScore) {
                    neighbor.parent = current
                    neighbor.gScore = tentativeGScore
                    neighbor.fScore = tentativeGScore + neighbor.heuristic

                    if (!openSet.contains(neighbor)) {
                        openSet.add(neighbor)
                    }
                }
            }
        }

        return emptyList()
    }

    private fun reconstructPath(node: GraphNode): List<Int> {
        val path = mutableListOf<Int>()
        var current: GraphNode? = node

        while (current != null) {
            path.add(0, current.id)
            current = current.parent
        }

        return path
    }
}
