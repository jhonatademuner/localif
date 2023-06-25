import cv2
import os

def pgmConverter(inputPath, outputPath):
    grayImage = cv2.imread(inputPath, cv2.IMREAD_GRAYSCALE)
    grayImage = cv2.resize(grayImage, (480, 800))
    cv2.imwrite(outputPath, grayImage, [cv2.IMWRITE_PXM_BINARY, 0])

def main():
    inputDirectory = "base-images"
    outputDirectory = "img"
    i= 0
    for filename in os.listdir(inputDirectory):
        inputPath = os.path.join(inputDirectory, filename)
        outputPath = os.path.join(outputDirectory, filename.replace(".png", ".pgm"))
        pgmConverter(inputPath, outputPath)
        i += 1

    print("Imagens convertidas com sucesso!")

if __name__ == "__main__":
    main()