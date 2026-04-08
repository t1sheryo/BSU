package com.example.imagegallery

import android.app.Activity
import android.content.Context
import android.content.Intent
import android.net.Uri
import android.os.Bundle
import android.provider.MediaStore
import android.view.View
import android.widget.Button
import android.widget.ImageView
import android.widget.TextView
import android.widget.Toast
import androidx.activity.result.contract.ActivityResultContracts
import androidx.fragment.app.Fragment

class ImagePickerFragment : Fragment(R.layout.fragment_image_picker) {

    private val imagePickerLauncher =
        registerForActivityResult(ActivityResultContracts.StartActivityForResult()) { result ->
            if (result.resultCode == Activity.RESULT_OK) {
                val imageUri = result.data?.data
                if (imageUri != null) {
                    saveSelectedImageUri(imageUri)
                    showSelectedImage(imageUri)
                } else {
                    Toast.makeText(
                        requireContext(),
                        getString(R.string.error_image_not_selected),
                        Toast.LENGTH_SHORT
                    ).show()
                }
            }
        }

    private lateinit var imageView: ImageView
    private lateinit var uriTextView: TextView

    override fun onViewCreated(view: View, savedInstanceState: Bundle?) {
        super.onViewCreated(view, savedInstanceState)

        imageView = view.findViewById(R.id.imageViewSelected)
        uriTextView = view.findViewById(R.id.textViewUri)
        val pickButton: Button = view.findViewById(R.id.buttonPickImage)

        pickButton.setOnClickListener {
            openImagePicker()
        }

        val savedUri = getSavedImageUri()
        if (savedUri != null) {
            showSelectedImage(savedUri)
        } else {
            showEmptyState()
        }
    }

    private fun openImagePicker() {
        val intent = Intent(Intent.ACTION_PICK, MediaStore.Images.Media.EXTERNAL_CONTENT_URI).apply {
            type = "image/*"
        }
        imagePickerLauncher.launch(intent)
    }

    private fun saveSelectedImageUri(uri: Uri) {
        getPrefs()
            .edit()
            .putString(KEY_SELECTED_IMAGE_URI, uri.toString())
            .apply()
    }

    private fun getSavedImageUri(): Uri? {
        val uriString = getPrefs().getString(KEY_SELECTED_IMAGE_URI, null)
        return if (uriString.isNullOrBlank()) null else Uri.parse(uriString)
    }

    private fun showSelectedImage(uri: Uri) {
        runCatching {
            imageView.setImageURI(uri)
        }.onSuccess {
            imageView.contentDescription = getString(R.string.selected_image_content_description)
            uriTextView.text = getString(R.string.uri_value, uri.toString())
        }.onFailure {
            showEmptyState()
            Toast.makeText(
                requireContext(),
                getString(R.string.error_saved_uri_unavailable),
                Toast.LENGTH_SHORT
            ).show()
        }
    }

    private fun showEmptyState() {
        imageView.setImageResource(R.drawable.ic_image_placeholder)
        imageView.contentDescription = getString(R.string.placeholder_image_content_description)
        uriTextView.text = getString(R.string.uri_placeholder)
    }

    private fun getPrefs() =
        requireContext().getSharedPreferences(PREFS_NAME, Context.MODE_PRIVATE)

    companion object {
        private const val PREFS_NAME = "image_gallery_prefs"
        private const val KEY_SELECTED_IMAGE_URI = "selected_image_uri"

        fun newInstance() = ImagePickerFragment()
    }
}
