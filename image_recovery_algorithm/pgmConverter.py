import cv2
import os

def pgmConverter(inputPath, outputPath):
    grayImage = cv2.imread(inputPath, cv2.IMREAD_GRAYSCALE)
    cv2.imwrite(outputPath, grayImage, [cv2.IMWRITE_PXM_BINARY, 0])

def main():
    inputDirectory = "base-images"
    outputDirectory = "img"

    for filename in os.listdir(inputDirectory):
        inputPath = os.path.join(inputDirectory, filename)
        outputPath = os.path.join(outputDirectory, filename.replace(".jpg", ".pgm"))
        pgmConverter(inputPath, outputPath)

    print("Imagens convertidas com sucesso!")

if __name__ == "__main__":
    main()