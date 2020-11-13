package com.example.casanova

import android.view.LayoutInflater
import android.view.ViewGroup
import android.widget.TextView
import androidx.recyclerview.widget.RecyclerView
import org.w3c.dom.Text

class SAdapter(private val dataSet: ArrayList<String>) : RecyclerView.Adapter<SAdapter.SViewHolder>() {

    class SViewHolder(val textView: TextView): RecyclerView.ViewHolder(textView)

    override fun onCreateViewHolder(parent: ViewGroup, viewType: Int): SViewHolder {

        val textView = LayoutInflater.from(parent.context)
            .inflate(R.layout.item_recycler, parent, false) as TextView

        return SViewHolder(textView)
    }

    override fun onBindViewHolder(holder: SViewHolder, position: Int) {
        holder.textView.text = dataSet[position]
    }

    override fun getItemCount(): Int {
        return dataSet.size
    }

    public fun addData(data: String) {
        dataSet.add(data)
        notifyDataSetChanged()
    }

}