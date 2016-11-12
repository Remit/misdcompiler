$(function(){
var cy = cytoscape({
   container: document.getElementById('cy'),
   boxSelectionEnabled: false,
   autounselectify: true,

   style: cytoscape.stylesheet()
		.selector('node')
			.css({
				'height': 80,
				'width': 80,
				'background-fit': 'cover',
				'border-color': '#000',
				'border-width': 3,
				'border-opacity': 0.5
			})
		.selector('edge')
			.css({
				'width': 6,
				'target-arrow-shape': 'triangle',
				'line-color': '#ffaaaa',
				'target-arrow-color': '#ffaaaa',
				'curve-style': 'bezier'
			})
		.selector('#13')
			.css({
				'background-image': 'Cytospace/images/spu/Processing.jpg'
				})
		.selector('#14')
			.css({
				'background-image': 'Cytospace/images/spu/Branch_begin.jpg'
				})
		.selector('#15')
			.css({
				'background-image': 'Cytospace/images/cpu/Branch_end.jpg'
				})
		.selector('#16')
			.css({
				'background-image': 'Cytospace/images/cpu/Terminator.jpg'
				})
		.selector('#17')
			.css({
				'background-image': 'Cytospace/images/cpu/Terminator.jpg'
				})
		.selector('#18')
			.css({
				'background-image': 'Cytospace/images/spu/Receive.jpg'
				})
		.selector('#20')
			.css({
				'background-image': 'Cytospace/images/cpu/Receive.jpg'
				})
		.selector('#1')
			.css({
				'background-image': 'Cytospace/images/spu/Data_structure.jpg',
				'label': 'STRUCT1'
				})
		.selector('#2')
			.css({
				'background-image': 'Cytospace/images/spu/Data_structure.jpg',
				'label': 'STRUCT2'
				})
		.selector('#8')
			.css({
				'background-image': 'Cytospace/images/cpu/Data_simple_tmp.jpg',
				'label': 'x'
				})
		.selector('#19')
			.css({
				'background-image': 'Cytospace/images/spu/Data_tag.jpg',
				'label': ''
				}),
   elements: {
      nodes: [
		{ data: { id: '13' }, position: { x: 0, y: 600 } },
		{ data: { id: '14' }, position: { x: 0, y: 300 } },
		{ data: { id: '15' }, position: { x: 0, y: 450 } },
		{ data: { id: '16' }, position: { x: 0, y: 0 } },
		{ data: { id: '17' }, position: { x: 0, y: 600 } },
		{ data: { id: '18' }, position: { x: 0, y: 150 } },
		{ data: { id: '20' }, position: { x: 0, y: 450 } },
		{ data: { id: '1' }, position: { x: 800, y: 0 } },
		{ data: { id: '2' }, position: { x: 800, y: 150 } },
		{ data: { id: '8' }, position: { x: 800, y: 300 } },
		{ data: { id: '19' }, position: { x: 800, y: 450 } }
      ],
      edges: [
		{ data: { source: '2', target: '13' } },
		{ data: { source: '8', target: '13' } },
		{ data: { source: '13', target: '1' } },
		{ data: { source: '13', target: '14' } },
		{ data: { source: '14', target: '15' } },
		{ data: { source: '14', target: '20' } },
		{ data: { source: '15', target: '17' } },
		{ data: { source: '16', target: '18' } },
		{ data: { source: '18', target: '19' } },
		{ data: { source: '18', target: '14' } },
		{ data: { source: '19', target: '14' } },
		{ data: { source: '20', target: '8' } },
		{ data: { source: '20', target: '13' } },
		{ data: { source: '13', target: '11' } }
      ]
   },
   layout: {
		name: 'preset',
		directed: true,
		padding: 10
	}
});
});
