const { dialog } = require('electron');
const fs = require('fs');
const jpeg = require('jpeg-js');
const pngjs = require('pngjs').PNG;
const bmp = require('bmp-js');
const tiff = require('utif');

// Добавляем обработчик для input элемента
document.getElementById('fileInput').addEventListener('change', handleFileSelect);

// Обработка выбора файлов
function handleFileSelect(event) {
    const files = event.target.files;
    const tableBody = document.getElementById('tableBody');
    tableBody.innerHTML = ''; // Очищаем таблицу перед загрузкой новых файлов

    Array.from(files).forEach(file => {
        const fileName = file.name;
        const reader = new FileReader();

        reader.onload = function(e) {
            const fileType = file.type;

            if (fileType.match('image/jpeg')) {
                handleJPEG(file, fileName);
            } else if (fileType.match('image/png')) {
                handlePNG(file, fileName);
            } else if (fileType.match('image/gif')) {
                handleGIF(file, fileName);
            } else if (fileType.match('image/bmp')) {
                handleBMP(file, fileName);
            } else if (fileType.match('image/tiff')) {
                handleTIFF(file, fileName);
            } else {
                console.log('Unsupported file type: ', fileType);
            }
        };

        reader.readAsArrayBuffer(file);
    });
}

// Функция для добавления строки в таблицу с информацией об изображении
function addRowToTable(fileInfo) {
    const tableBody = document.getElementById('tableBody');
    const row = document.createElement('tr');

    const fileNameCell = document.createElement('td');
    fileNameCell.textContent = fileInfo.name;
    row.appendChild(fileNameCell);

    const dimensionsCell = document.createElement('td');
    dimensionsCell.textContent = fileInfo.dimensions;
    row.appendChild(dimensionsCell);

    const resolutionCell = document.createElement('td');
    resolutionCell.textContent = fileInfo.resolution;
    row.appendChild(resolutionCell);

    const colorDepthCell = document.createElement('td');
    colorDepthCell.textContent = fileInfo.colorDepth;
    row.appendChild(colorDepthCell);

    const compressionCell = document.createElement('td');
    compressionCell.textContent = fileInfo.compression;
    row.appendChild(compressionCell);

    tableBody.appendChild(row);
}

// Обработка файлов JPEG
function handleJPEG(file, fileName) {
    const reader = new FileReader();
    reader.onload = function(event) {
        const data = event.target.result;
        const jpegData = jpeg.decode(new Uint8Array(data), true);
        const fileInfo = {
            name: fileName,
            dimensions: `${jpegData.width}x${jpegData.height}`,
            resolution: 'N/A', // EXIF данные могут быть добавлены при необходимости
            colorDepth: jpegData.components * 8,
            compression: 'JPEG Compression'
        };
        addRowToTable(fileInfo);
    };
    reader.readAsArrayBuffer(file);
}

// Обработка файлов PNG
function handlePNG(file, fileName) {
    const reader = new FileReader();
    reader.onload = function(event) {
        const data = new Uint8Array(event.target.result);
        const png = new pngjs();
        png.parse(data, function(error, pngData) {
            if (error) throw error;
            const fileInfo = {
                name: fileName,
                dimensions: `${pngData.width}x${pngData.height}`,
                resolution: 'N/A',
                colorDepth: pngData.depth * pngData.channels,
                compression: 'Deflate (PNG)'
            };
            addRowToTable(fileInfo);
        });
    };
    reader.readAsArrayBuffer(file);
}

// Обработка файлов GIF
function handleGIF(file, fileName) {
    const reader = new FileReader();
    reader.onload = function(event) {
        const data = event.target.result;
        const gif = require('omggif');
        const parser = new gif.GifReader(new Uint8Array(data));
        const fileInfo = {
            name: fileName,
            dimensions: `${parser.width}x${parser.height}`,
            resolution: 'N/A',
            colorDepth: '8-bit (GIF)',
            compression: 'LZW Compression (GIF)'
        };
        addRowToTable(fileInfo);
    };
    reader.readAsArrayBuffer(file);
}

// Обработка файлов BMP
function handleBMP(file, fileName) {
    const reader = new FileReader();
    reader.onload = function(event) {
        const data = event.target.result;
        const bmpData = bmp.decode(new Uint8Array(data));
        const fileInfo = {
            name: fileName,
            dimensions: `${bmpData.width}x${bmpData.height}`,
            resolution: 'N/A',
            colorDepth: bmpData.bitPP,
            compression: 'None (BMP)'
        };
        addRowToTable(fileInfo);
    };
    reader.readAsArrayBuffer(file);
}

// Обработка файлов TIFF
function handleTIFF(file, fileName) {
    const reader = new FileReader();
    reader.onload = function(event) {
        const data = new Uint8Array(event.target.result);
        const tiffData = tiff.decode(data);
        const firstPage = tiffData[0]; // Первое изображение в TIFF (многослойные файлы)
        const width = firstPage.width;
        const height = firstPage.height;
        const fileInfo = {
            name: fileName,
            dimensions: `${width}x${height}`,
            resolution: `${firstPage.XResolution}x${firstPage.YResolution} dpi`,
            colorDepth: firstPage.bitsPerSample[0],
            compression: 'TIFF Compression (LZW/None, etc.)'
        };
        addRowToTable(fileInfo);
    };
    reader.readAsArrayBuffer(file);
}
