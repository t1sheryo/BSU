const colorPicker = document.getElementById('colorPicker');
const colorDisplay = document.getElementById('colorDisplay');
const rgbValue = document.getElementById('rgbValue');
const hlsValue = document.getElementById('hlsValue');
const cmykValue = document.getElementById('cmykValue');

function updateColorDisplay(color) {
  colorDisplay.style.backgroundColor = color;

  const rgb = hexToRgb(color);
  rgbValue.textContent = `rgb(${rgb.r}, ${rgb.g}, ${rgb.b})`;

  const hls = rgbToHls(rgb.r, rgb.g, rgb.b);
  hlsValue.textContent = `hls(${Math.round(hls.h)}, ${Math.round(hls.s)}%, ${Math.round(hls.l)}%)`;

  const cmyk = rgbToCmyk(rgb.r, rgb.g, rgb.b);
  cmykValue.textContent = `cmyk(${Math.round(cmyk.c)}, ${Math.round(cmyk.m)}, ${Math.round(cmyk.y)}, ${Math.round(cmyk.k)})`;
  document.getElementById('c').value = Math.round(cmyk.c);
  document.getElementById('m').value = Math.round(cmyk.m);
  document.getElementById('y').value = Math.round(cmyk.y);
  document.getElementById('k').value = Math.round(cmyk.k);
}

function rgbToCmyk(r, g, b) {

  let k = Math.min(1 - r / 255, 1 - g / 255, 1 - b / 255);
  let c = (1 - r / 255 - k) / (1 - k) || 0;
  let m = (1 - g / 255 - k) / (1 - k) || 0;
  let y = (1 - b / 255 - k) / (1 - k) || 0;

  c *= 100;
  m *= 100;
  y *= 100;
  k *= 100;

  return { c, m, y, k };
}

function hexToRgb(hex) {
  const bigint = parseInt(hex.slice(1), 16);
  const r = (bigint >> 16) & 255;
  const g = (bigint >> 8) & 255;
  const b = bigint & 255;
  return { r, g, b };
}

function rgbToHls(r, g, b) {
  r /= 255;
  g /= 255;
  b /= 255;
  
  const max = Math.max(r, g, b);
  const min = Math.min(r, g, b);
  let h, s, l = (max + min) / 2;

  if (max === min) {
    h = s = 0;
  } else {
    const d = max - min;
    s = l > 0.5 ? d / (2 - max - min) : d / (max + min);
    
    switch (max) {
      case r: h = (g - b) / d + (g < b ? 6 : 0); break;
      case g: h = (b - r) / d + 2; break;
      case b: h = (r - g) / d + 4; break;
    }
    
    h /= 6;
  }

  return {
    h: h * 360,
    s: s * 100,
    l: l * 100
  };
}

function rgbToHex(r, g, b) {
  return `#${((1 << 24) | (r << 16) | (g << 8) | b).toString(16).slice(1).toUpperCase()}`;
}

function cmykToRgb(c, m, y, k) {
  c /= 100;
  m /= 100;
  y /= 100;
  k /= 100;

  let r = 255 * (1 - c) * (1 - k);
  let g = 255 * (1 - m) * (1 - k);
  let b = 255 * (1 - y) * (1 - k);

  r = Math.round(r);
  g = Math.round(g);
  b = Math.round(b);

  return { r, g, b };
}

function updateOutputs() {
  const c = parseFloat(document.getElementById('c').value);
  const m = parseFloat(document.getElementById('m').value);
  const y = parseFloat(document.getElementById('y').value);
  const k = parseFloat(document.getElementById('k').value);

  const maxValue = 100, minValue = 0;
  if (c > maxValue || m > maxValue || y > maxValue || k > maxValue || c < minValue || m < minValue || y < minValue || k < minValue) {
    alert("Not correct number! All parameters(c, m, y, k) are set to 0!");
    c = 0;
    m = 0;
    y = 0;
    k = 0;
  }

  const rgb = cmykToRgb(c, m, y, k);
  const hexColor = rgbToHex(rgb.r, rgb.g, rgb.b);
  updateColorDisplay(hexColor);
}

document.querySelectorAll('input[type="number"]').forEach(input => {
  input.addEventListener('input', updateOutputs);
});

colorPicker.addEventListener('input', (event) => {
  const color = event.target.value;
  updateColorDisplay(color);
});

updateColorDisplay(colorPicker.value);
updateOutputs();