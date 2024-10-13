const colorPicker = document.getElementById('colorPicker');
const colorDisplay = document.getElementById('colorDisplay');
const rgbValue = document.getElementById('rgbValue');
const hlsValue = document.getElementById('hlsValue');
const cmykValue = document.getElementById('cmykValue');
const Warning = document.getElementById('Warning');

document.getElementById('system-select').addEventListener('change', function() {
  const selectedValue = this.value;
  document.getElementById('rgbInputs').classList.add('hidden');
  document.getElementById('hlsInputs').classList.add('hidden');
  document.getElementById('cmykInputs').classList.add('hidden');
  
  if (selectedValue === 'rgb') {
    document.getElementById('rgbInputs').classList.remove('hidden');
  } else if (selectedValue === 'hls') {
    document.getElementById('hlsInputs').classList.remove('hidden');
  } else if (selectedValue === 'cmyk') {
    document.getElementById('cmykInputs').classList.remove('hidden');
  }
});

function updateColorDisplay(color) {
  colorDisplay.style.backgroundColor = color;

  const rgb = hexToRgb(color);
  rgbValue.textContent = `rgb(${rgb.r}, ${rgb.g}, ${rgb.b})`;

  const hls = rgbToHls(rgb.r, rgb.g, rgb.b);
  hlsValue.textContent = `hls(${Math.round(hls.h)}, ${Math.round(hls.s)}%, ${Math.round(hls.l)}%)`;

  const cmyk = rgbToCmyk(rgb.r, rgb.g, rgb.b);
  cmykValue.textContent = `cmyk(${Math.round(cmyk.c)}, ${Math.round(cmyk.m)}, ${Math.round(cmyk.y)}, ${Math.round(cmyk.k)})`;
  // document.getElementById('c').value = Math.round(cmyk.c);
  // document.getElementById('m').value = Math.round(cmyk.m);
  // document.getElementById('y').value = Math.round(cmyk.y);
  // document.getElementById('k').value = Math.round(cmyk.k);
}

function updateOutputsCmyk() {
  let c = parseFloat(document.getElementById('c').value);
  let m = parseFloat(document.getElementById('m').value);
  let y = parseFloat(document.getElementById('y').value);
  let k = parseFloat(document.getElementById('k').value);

  const maxValue = 100, minValue = 0;
  if (c > maxValue || m > maxValue || y > maxValue || k > maxValue || c < minValue || m < minValue || y < minValue || k < minValue) {
    Warning.innerText = "Not correct number! All parameters(c, m, y, k) are set to 0!";
    c = 0;  
    m = 0;
    y = 0;
    k = 0;
  }

  const rgb = cmykToRgb(c, m, y, k);
  const hexColor = rgbToHex(rgb.r, rgb.g, rgb.b);
  updateColorDisplay(hexColor);
}

function updateOutputsRgb() {
  let r = parseFloat(document.getElementById('r').value);
  let g = parseFloat(document.getElementById('g').value);
  let b = parseFloat(document.getElementById('b').value);

  const hexValue = rgbToHex(r, g, b);
  updateColorDisplay(hexValue);

  const maxValue = 255, minValue = 0;
  if (r > maxValue || g > maxValue || b > maxValue || r < minValue || g < minValue || b < minValue) {
    Warning.innerText = "Not correct number! All parameters(r, g, b) are set to 0!";
    r = 0;
    g = 0;
    b = 0;
  }

  //const rgb = cmykToRgb(c, m, y, k);
  const hexColor = rgbToHex(r, g, b);
  updateColorDisplay(hexColor);
}

function updateOutputsHls() {
  let h = parseFloat(document.getElementById('h').value);
  let l = parseFloat(document.getElementById('l').value);
  let s = parseFloat(document.getElementById('s').value);

  const hexValue = hlsToHex(h, l, s);
  updateColorDisplay(hexValue);

  const maxValue = 100, minValue = 0;
  if (h > 360 || l > maxValue || s > maxValue || h < minValue || l < minValue || s < minValue) {
    Warning.innerText = "Not correct number! All parameters(h, l, s) are set to 0!";
    h = 0;
    l = 0;
    s = 0;
  }

  //const rgb = cmykToRgb(c, m, y, k);
  const hexColor = hlsToHex(h, l, s);
  updateColorDisplay(hexColor);
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

function hlsToHex(h, l, s) {
  h /= 360;
  l /= 100;
  s /= 100;

  let r, g, b;

  if (s === 0) {
    r = g = b = l;
  } else {
    const hueToRgb = (p, q, t) => {
      if (t < 0) t += 1;
      if (t > 1) t -= 1;
      if (t < 1/6) return p + (q - p) * 6 * t;
      if (t < 1/2) return q;
      if (t < 2/3) return p + (q - p) * (2/3 - t) * 6;
      return p;
    };

    const q = l < 0.5 ? l * (1 + s) : l + s - l * s;
    const p = 2 * l - q;

    r = hueToRgb(p, q, h + 1/3);
    g = hueToRgb(p, q, h);
    b = hueToRgb(p, q, h - 1/3);
  }

  const toHex = x => {
    const hex = Math.round(x * 255).toString(16);
    return hex.length === 1 ? '0' + hex : hex;
  };

  return `#${toHex(r)}${toHex(g)}${toHex(b)}`;
}

// document.querySelectorAll('input[type="number"]').forEach(input => {
//   input.addEventListener('input', updateOutputs);
// });

document.querySelectorAll('.inputValRgb').forEach(element => {
  element.addEventListener('input', updateOutputsRgb)
});

document.querySelectorAll('.inputValHls').forEach(element => {
  element.addEventListener('input', updateOutputsHls)
});

document.querySelectorAll('.inputValCmyk').forEach(element => {
  element.addEventListener('input', updateOutputsCmyk)
});

colorPicker.addEventListener('input', (event) => {
  const color = event.target.value;
  updateColorDisplay(color);
});

updateColorDisplay(colorPicker.value);
updateOutputsRgb();
updateOutputsHls();
updateOutputsCmyk();